#include <linux/kernel.h>
#include <linux/linkage.h>

asmlinkage long sys_simple_add(int a, int b, int *x)
{
	(*x) = a + b;
	printk(KERN_ALERT "\nThe sum of %d and %d = %d\n", a, b, (*x));
	return 0;
}
