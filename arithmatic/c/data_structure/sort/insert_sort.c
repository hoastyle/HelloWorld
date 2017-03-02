#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TYPE int

void swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void print_array(TYPE list[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

static TYPE list[5] = {3, 1, 5, 2, 8};

/*
 * 查找并位移
 */
static TYPE* insert_sort_opt(TYPE list[], int n)
{
	int i, j, key;
	TYPE *list_copy = (int *)malloc(n * sizeof(TYPE));

	memcpy(list_copy, list, 4 * n);

	for (j = 1; j < n; j++) {
		key = list_copy[j];

		i = j - 1;
		while ( list_copy[i] > key && i >= 0 ) {
			list_copy[i + 1] = list_copy[i];
			i = i - 1;
		}

		list_copy[i + 1] = key;
	}

	printf("%s\n", __func__);
	return list_copy;
}

/* 
 * - 查找位置
 * - 整体位移
 * - 插入
 */
static TYPE* insert_sort_org(TYPE list[], int n)
{
	int i, j, k, key;
	TYPE *list_copy = (int *)malloc(n * sizeof(TYPE));

	memcpy(list_copy, list, 4 * n);

	//从小到大
	for (j = 1; j < n; j++) {
		//查找a[j] > a[i]位置, i + 1是将要插入的位置
		key = list_copy[j];
		for (i = j - 1; i >= 0; i--)
			if (list_copy[i] < key)
				break;

		//将i+1 - j-1 -> i+2 - j, a[i+1] = insert 
		if (i != j - 1) {
			//一定要从后向前，否则会破坏数据
			for (k = j - 1; k > i; k--)
				list_copy[k + 1] = list_copy[k];
			list_copy[i + 1] = key;
		}
	}

	printf("%s\n", __func__);
	return list_copy;
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

	return list;
}

int main()
{
	int i;
	TYPE *list_copy;
	int n = sizeof(list)/sizeof(int);

	list_copy = insert_sort_opt(list, n);
	print_array(list_copy, n);
	list_copy = insert_sort_org(list, n);
	print_array(list_copy, n);
/*
	list_copy = select_sort(list, n);
	for (i = 0; i < n; i ++)
		printf("%d ", list_copy[i]);
	printf("\n");
	list_copy = bubble_sort(list, n);
	for (i = 0; i < n; i ++)
		printf("%d ", list_copy[i]);
	printf("\n");
	for (i = 0; i < n; i ++)
		printf("%d ", list[i]);
	printf("\n");
	shell_sort(list, n);
	for (i = 0; i < n; i ++)
		printf("%d ", list[i]);
	printf("\n");
*/

	return 0;
}
