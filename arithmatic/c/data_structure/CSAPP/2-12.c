#include <stdio.h>

void bit_op1(long long int *);

int main()
{
	long long int x = 0x8765432187654321;
	bit_op1(&x);
	printf("bit_op1: 0x%llx\n", x);
}

void bit_op1(long long int *x)
{
	int temp;
	temp = (*x >> 8 << 8) ^ *x;
	*x = temp;
}

void bit_op2()
{

}

void bit_op3()
{

}
