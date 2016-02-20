#include <stdio.h>

int i, j, var = 0;

void up_sort(int a[])
{
	printf("start up sort\n");
	for(j = 2; j < 6; j++) {
		var = a[j];
		i = j - 1;

		while (i > 0 && a[i] > var) {
			a[i + 1] = a[i];
			i = i - 1;
		}

		a[i + 1] = var;

		for(i = 1; i < j + 1; i++) {
			if( i == j )
				printf("\n");
			else
				printf("%d ", a[i]);
		}
	}

	for(i = 1; i < 6; i++)
		printf("%d ", a[i]);

	printf("\n");
}

void down_sort(int a[])
{
	printf("start down sort\n");
	for(j = 2; j < 6; j++) {
		var = a[j];
		i = j - 1;

		while (i > 0 && a[i] < var) {
			a[i + 1] = a[i];
			i = i - 1;
		}

		a[i + 1] = var;

		for(i = 1; i < j + 1; i++) {
			if( i == j )
				printf("\n");
			else
				printf("%d ", a[i]);
		}
	}

	for(i = 1; i < 6; i++)
		printf("%d ", a[i]);

	printf("\n");
}

void main()
{
	int a[6] = {0, 4, 2, 1, 5, 3};
//	int i, j, var = 0;

	up_sort(a);

	down_sort(a);
}
