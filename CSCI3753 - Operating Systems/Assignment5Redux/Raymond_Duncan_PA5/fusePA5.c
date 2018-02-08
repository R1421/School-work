/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  Minor modifications and note by Andy Sayler (2012) <www.andysayler.com>

  Source: fuse-2.8.7.tar.gz examples directory
  http://sourceforge.net/projects/fuse/files/fuse-2.X/

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall `pkg-config fuse --cflags` fusexmp.c -o fusexmp `pkg-config fuse --libs`

  Note: This implementation is largely stateless and does not maintain
        open file handels between open and release calls (fi->fh).
        Instead, files are opened and closed as necessary inside read(), write(),
        etc calls. As such, the functions that rely on maintaining file handles are
        not implmented (fgetattr(), etc). Those seeking a more efficient and
        more complete implementation may wish to add fi->fh support to minimize
        open() and close() calls and support fh dependent functions.

*/

#define FUSE_USE_VERSION 28
#define HAVE_SETXATTR

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef linux
/* For pread()/pwrite() */
#define _XOPEN_SOURCE 500
#endif

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>

#include "aes-crypt.h"

#ifdef HAVE_SETXATTR
#include <sys/xattr.h>
#endif

#define PDATA ((struct privateData *) fuse_get_context()->private_data)

struct privateData {
	char *key;
	char *directory;
};

//The following function taken from pfeiffer fuse tutorial (http://www.cs.nmsu.edu/~pfeiffer/fuse-tutorial/src/bbfs.c)
static void fullpath(char fpath[PATH_MAX], const char *path)
{
	strcpy(fpath, PDATA->directory);
	strncat(fpath, path, PATH_MAX);
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
	int res;
	char fpath[PATH_MAX];

	fullpath(fpath,path);

	res = lstat(fpath, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_access(const char *path, int mask)
{
	int res;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	res = access(fpath, mask);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readlink(const char *path, char *buf, size_t size)
{
	int res;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	res = readlink(fpath, buf, size - 1);
	if (res == -1)
		return -errno;

	buf[res] = '\0';
	return 0;
}


static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
	DIR *dp;
	struct dirent *de;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		if (filler(buf, de->d_name, &st, 0))
			break;
	}

	closedir(dp);
	return 0;
}

static int xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
	int res;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	/* On Linux this could just be 'mknod(path, mode, rdev)' but this
	   is more portable */
	if (S_ISREG(mode)) {
		res = open(fpath, O_CREAT | O_EXCL | O_WRONLY, mode);
		if (res >= 0)
			res = close(res);
	} else if (S_ISFIFO(mode))
		res = mkfifo(fpath, mode);
	else
		res = mknod(fpath, mode, rdev);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
	int res;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	res = mkdir(fpath, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_unlink(const char *path)
{
	int res;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	res = unlink(fpath);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_rmdir(const char *path)
{
	int res;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	res = rmdir(fpath);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_symlink(const char *from, const char *to)
{
	int res;
        char fpathFrom[PATH_MAX];
        char fpathTo[PATH_MAX];

        fullpath(fpathFrom,from);
        fullpath(fpathTo,to);


	res = symlink(fpathFrom, fpathTo);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_rename(const char *from, const char *to)
{
	int res;
        char fpathFrom[PATH_MAX];
        char fpathTo[PATH_MAX];

        fullpath(fpathFrom,from);
        fullpath(fpathTo,to);

	res = rename(fpathFrom, fpathTo);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_link(const char *from, const char *to)
{
	int res;
        char fpathFrom[PATH_MAX];
        char fpathTo[PATH_MAX];

        fullpath(fpathFrom,from);
        fullpath(fpathTo,to);

	res = link(fpathFrom, fpathTo);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
	int res;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	res = chmod(fpath, mode);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid)
{
	int res;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	res = lchown(fpath, uid, gid);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_truncate(const char *path, off_t size)
{
	int res;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	res = truncate(fpath, size);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_utimens(const char *path, const struct timespec ts[2])
{
	int res;
	struct timeval tv[2];
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	tv[0].tv_sec = ts[0].tv_sec;
	tv[0].tv_usec = ts[0].tv_nsec / 1000;
	tv[1].tv_sec = ts[1].tv_sec;
	tv[1].tv_usec = ts[1].tv_nsec / 1000;

	res = utimes(fpath, tv);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
	int res;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	res = open(fpath, fi->flags);
	if (res == -1)
		return -errno;

	close(res);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
	FILE *fid;
	int res;
        char fpath[PATH_MAX];
	char fpath2[PATH_MAX];
	char *key;
	FILE *temp;
	int sz;
	int action;

        fullpath(fpath,path);
	fullpath(fpath2,"/.temp");
	key = PDATA->key;
	action = -1;

	(void) fi;
	(void) size;
//	fd = open(fpath, O_RDONLY);
	fid = fopen(fpath, "r+");
	temp = fopen(fpath2, "w+");

//	res = getxattr(fpath, "user.pa5-encfs.encrypted", "true", strlen("true"));
        res = getxattr(fpath, "user.pa5-encfs.encrypted", 0, 0);
	if(res != -1)
		action = 0;

	res = do_crypt((FILE *)fid, (FILE *) temp, action, key);
	if(res != 1){
		fprintf(stdout, "Could not decrypt file!\n");
	}
	fseek(temp, 0L,SEEK_END);
	sz = ftell(temp);
	fseek(temp,0L,SEEK_SET);
	res = pread(fileno(temp), buf, sz, offset);
	if (res == -1)
		res = -errno;

//	res = unlink(fpath2);
	if(res == -1)
		res = -errno;

	fclose(fid);
	fclose(temp);
	return res;
}

static int xmp_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi)
{
	FILE *fid;
	FILE *temp;
	int res;
	int sz;
	int action;
	int action2;
        char fpath[PATH_MAX];
	char fpath2[PATH_MAX];

        fullpath(fpath,path);
	fullpath(fpath2,"/.temp");
	action = -1;
	action2 = -1;


	(void) fi;
//	fd = open(fpath, O_WRONLY);
	fid = fopen(fpath,"r");
	temp = fopen(fpath2,"w+");
	
//	res = getxattr(fpath, "user.pa5-encfs.encrypted", "true", strlen("true"));
        res = getxattr(fpath, "user.pa5-encfs.encrypted", 0, 0);
	if(res != -1){
		action = 0;
		action2 = 1;
	}

	do_crypt(fid, temp, action, PDATA->key);
	fclose(fid);
	fseek(temp, 0L,SEEK_END);
	sz = ftell(temp);
	fseek(temp,0L,SEEK_SET);
	
	res = pwrite(fileno(temp), buf, size, offset);
	if (res == -1)
		res = -errno;

	fid = fopen(fpath,"w");
	do_crypt(temp, fid, action2, PDATA->key);
	fseek(fid, 0L,SEEK_END);
	sz = ftell(fid);
	fseek(fid,0L,SEEK_SET);
	

	fclose(temp);
	fclose(fid);

	return sz;
}

static int xmp_statfs(const char *path, struct statvfs *stbuf)
{
	int res;
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	res = statvfs(fpath, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_create(const char* path, mode_t mode, struct fuse_file_info* fi) {

    FILE *fid;
    (void) fi;
    (void) mode;
    char fpath[PATH_MAX];

    fullpath(fpath,path);

    int res;
//    res = creat(fpath, mode);
    fid = fopen(fpath,"w+");
    res = do_crypt(fid, fid, 1, PDATA->key);

    if(res == -1)
	return -errno;

//    res = setxattr(fpath, "user.pa5-encfs.encrypted", "true", strlen("true"), 0);
    res = setxattr(fpath, "user.pa5-encfs.encrypted", 0, 0, 0);
    if(res == -1)
	return -errno;

    fclose(fid);

    return 0;
}


static int xmp_release(const char *path, struct fuse_file_info *fi)
{
	/* Just a stub.	 This method is optional and can safely be left
	   unimplemented */
	char fpath[PATH_MAX];
	int res = 0;

	(void) fi;
	(void) path;

	fullpath(fpath,"/.temp");
	res = remove(fpath);

	return res;
}

static int xmp_fsync(const char *path, int isdatasync,
		     struct fuse_file_info *fi)
{
	/* Just a stub.	 This method is optional and can safely be left
	   unimplemented */

	(void) path;
	(void) isdatasync;
	(void) fi;
	return 0;
}

#ifdef HAVE_SETXATTR
static int xmp_setxattr(const char *path, const char *name, const char *value,
			size_t size, int flags)
{
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	int res = lsetxattr(fpath, name, value, size, flags);
	if (res == -1)
		return -errno;
	return 0;
}

static int xmp_getxattr(const char *path, const char *name, char *value,
			size_t size)
{
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	int res = lgetxattr(fpath, name, value, size);
	if (res == -1)
		return -errno;
	return res;
}

static int xmp_listxattr(const char *path, char *list, size_t size)
{
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	int res = llistxattr(fpath, list, size);
	if (res == -1)
		return -errno;
	return res;
}

static int xmp_removexattr(const char *path, const char *name)
{
        char fpath[PATH_MAX];

        fullpath(fpath,path);

	int res = lremovexattr(fpath, name);
	if (res == -1)
		return -errno;
	return 0;
}
#endif /* HAVE_SETXATTR */

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.access		= xmp_access,
	.readlink	= xmp_readlink,
	.readdir	= xmp_readdir,
	.mknod		= xmp_mknod,
	.mkdir		= xmp_mkdir,
	.symlink	= xmp_symlink,
	.unlink		= xmp_unlink,
	.rmdir		= xmp_rmdir,
	.rename		= xmp_rename,
	.link		= xmp_link,
	.chmod		= xmp_chmod,
	.chown		= xmp_chown,
	.truncate	= xmp_truncate,
	.utimens	= xmp_utimens,
	.open		= xmp_open,
	.read		= xmp_read,
	.write		= xmp_write,
	.statfs		= xmp_statfs,
	.create         = xmp_create,
	.release	= xmp_release,
	.fsync		= xmp_fsync,
#ifdef HAVE_SETXATTR
	.setxattr	= xmp_setxattr,
	.getxattr	= xmp_getxattr,
	.listxattr	= xmp_listxattr,
	.removexattr	= xmp_removexattr,
#endif
};

void usage()
{
	fprintf(stdout, "Usage: pa5-encfs <key phrase> <mirror directory> <mount point> <options>\n");
	exit(1);
	
}

int main(int argc, char *argv[])
{
	int i;
	char *key;
	char *mirror;

	struct privateData *pd = malloc(sizeof(struct privateData));

	//Parse argv for the <key phrase> and <mirror directory>. Leave on the mount point
	if(argc < 3 || argv[1][0] == '-' || argv[2][0] == '-' || argv[3][0] == '-') {
		usage();
	}


	key = argv[1];
	mirror = argv[2];
	argv[1] = argv[3];

	fprintf(stdout, "%s\n", argv[argc+2]);

	for(i = 1; i < argc; i++){
		if(i < argc-2){
			argv[i] = argv[i+2];
		}
		else{
			argv[i] = NULL;
		}
		fprintf(stdout, "%d: %s\n", i, argv[i]);
	}
	argc -= 2;
	pd->key = key;
	pd->directory = realpath(mirror, NULL);

	umask(0);
	return fuse_main(argc, argv, &xmp_oper, pd);
}
