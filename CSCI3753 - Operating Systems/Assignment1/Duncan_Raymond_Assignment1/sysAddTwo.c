#include <stdio.h>
#include <linux/kernel.h>
#include <syscall.h>
#include <errno.h>

int main()
{
	int a = 1;
	int b = 2;
	int x = 0;

	int e = syscall(401, a, b, &x);
	
	if(e != 0){
		printf("syscall returned %d\n errno = %d\n", e, errno);
		return -1;
	}
	printf("The sum of %d and %d is: %d\n\n\n", a, b, x);
	return 0;
}
