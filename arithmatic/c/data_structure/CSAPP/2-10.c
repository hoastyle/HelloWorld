#include <stdio.h>

void inplace_swap(int *, int *);
void reverse_array(int *, int);

int main()
{
	int a = 1;
	int b = 2;
	int i = 0;
	int array[7] = {1, 2, 3, 4, 5, 6, 7};
	int count = sizeof(array) / sizeof(int);

	printf("original:	a = %d, b = %d\n", a, b);
	inplace_swap(&a, &b);
	printf("result:		a = %d, b = %d\n", a, b);

	printf("original array: [");
	while( i < 6 ) {
		printf("%d, ", array[i]);
		i++;
	}
	printf("%d]\n", array[i]);

	reverse_array(array, count);

	i = 0;
	printf("reverse array: [");
	while( i < 6 ) {
		printf("%d, ", array[i]);
		i++;
	}
	printf("%d]\n", array[i]);
}

void inplace_swap(int *x, int *y)
{
	*x = *x ^ *y;
	*y = *x ^ *y;
	*x = *x ^ *y;
}

void reverse_array(int array[], int count)
{
	int front = 0;
	int rear = count - 1;

	while( front < rear ) {
		inplace_swap( array + front, array + rear );
		front++;
		rear--;
	}
}
