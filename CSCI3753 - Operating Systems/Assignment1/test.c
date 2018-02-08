#include <stdio.h>
#include <stdlib.h>
//#include "test.h"

void addtwo(int a, int b, int *x)
{
	(*x) = a + b;
	printf("Within addtwo, x = %d\n", (*x));
}

int main()
{
	int a = 1;
	int b = 1;
	//int *x = (int*) malloc(4);
	int x = 0;

	printf("The values for a and b are %d, and %d respectively.\n x = %d\n", a, b, x);
	printf("x before addtwo = %d\n", x);
	addtwo(a,b,&x);
	printf("x after addtwo = %d\n", x);

	//free(x);
	return 0;
}
