#include <stdio.h>
#include <linux/kernel.h>
#include <syscall.h>
#include <errno.h>
#include <unistd.h>


int main()
{
	int x;
	x = syscall(400);
	printf("Syscall returns %d\n", x);
	printf("Errno = %d\n", errno);
	return 0;
}	
