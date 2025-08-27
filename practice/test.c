#include <stdio.h>

extern int test(int,int);	// extern makes it accessible outside c program

int test(int a, int b)
{
	printf("HERE!\n");
	return(a + b);
}
