#include "common.h"
#include <string.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static TYPE list[5] = {3, 1, 5, 2, 8};

static void insert_sort(TYPE list[], int n)
{
	int i, j, key;

	for (j = 1; j < n; j++) {
		key = list[j];

//for
/*
		for (i = j - 1; list[i] > key && i >= 0; ) {
			list[i + 1] = list[i];
			i = i - 1;
		}
*/
// while
		i = j - 1;
		while( list[i] < key && i >= 0 ) {
			list[i + 1] = list[i];
			i = i - 1;
		}

		list[i + 1] = key;
	}
}

static TYPE *select_sort(TYPE list[], int n)
{
	int i, j, min, temp;
	TYPE *list_copy = (int *)malloc(n * sizeof(TYPE));

	memcpy(list_copy, list, 4 * n);

	for (i = 0; i < n; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (list_copy[j] < list_copy[min])
				min = j;
		}
		if (min != i) {
//			temp = list_copy[min];
//			list_copy[min] = list_copy[i];
//			list_copy[i] = temp;
			swap((list_copy + min), (list_copy + i));
		}
	}
	return list_copy;
}

static TYPE *bubble_sort(TYPE list[], int n)
{
	int i, j;
	TYPE *list_copy = (int *)malloc(n * sizeof(TYPE));

	memcpy(list_copy, list, 4 * n);

	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i - 1; j++) {
			//从小到大
			if (list_copy[j] > list_copy[j + 1])
				swap((list_copy + j), (list_copy + j + 1));
		}
	}
	return list_copy;
}

//为什么效率高
static TYPE *shell_sort(TYPE list[], int n)
{
	int gap, i, j, temp, k;

	gap = n;

//通过插入排序进行
	while (gap >= 1) {
		gap = gap/2;

		for (i = 0; i < gap; i++ )
			for (j = i + gap; j < n; j += gap) {
				temp = list[j];
				k = j - gap;
//k一定要>=0
				while ( k >= 0 && list[k] > temp ) {
					list[k + gap] = list[k];
					k -= gap;
				}
				list[k + gap] = temp;
			}
	}
}

int main()
{
	int i;
	TYPE *list_copy;
	int n = sizeof(list)/sizeof(int);

	//insert_sort(list, n);
	list_copy = select_sort(list, n);
	for (i = 0; i < n; i ++)
		printf("%d ", list_copy[i]);
	list_copy = bubble_sort(list, n);
	for (i = 0; i < n; i ++)
		printf("%d ", list_copy[i]);
	for (i = 0; i < n; i ++)
		printf("%d ", list[i]);
	shell_sort(list, n);
	for (i = 0; i < n; i ++)
		printf("%d ", list[i]);
	printf("\n");

	return 0;
}
