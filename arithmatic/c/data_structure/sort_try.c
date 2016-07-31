#include "common.h"
#include <stdlib.h>
#include <string.h>

void swap(TYPE *a, TYPE *b)
{
	TYPE temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void bubble_sort_v1(TYPE *base, int size)
{
	int i, j;

	for (i = size - 1; i >= 1; i--)
		for (j = 0; j < i; j++) {
			if (*(base + j) > *(base + j + 1))
				swap(base + j, base + j + 1);
		}
}

static TYPE *bubble_sort_v2(TYPE list[], int size)
{
	int i, j;
	TYPE *list_sort = (TYPE *)malloc(sizeof(TYPE) * size);

	memcpy(list_sort, list, sizeof(TYPE) * size);

	for (i = 0; i < size; i++)
		for (j = 0; j < size - i - 1; j++) {
			if (list_sort[j] > list_sort[j + 1])
				swap(list_sort + j, list_sort + j + 1);
		}

	return list_sort;
}

//采用冒泡的方式将新元素插入合适的位置
static TYPE *insert_sort_v1(TYPE list[], int size)
{
	int i, j;
	TYPE *list_sort = (TYPE *)malloc(sizeof(TYPE) * size);

	memcpy(list_sort, list, sizeof(TYPE) * size);

	for (i = 1; i < size; i++)
		for (j = i; j > 0; j--) {
			if (list_sort[j] < list_sort[j-1])
				swap(list_sort + j, list_sort + j - 1);
		}

	return list_sort;
}

static TYPE *insert_sort_v2(TYPE list[], int size)
{
	int i, j;
	TYPE temp;
	TYPE *list_sort = (TYPE *)malloc(sizeof(TYPE) * size);

	memcpy(list_sort, list, sizeof(TYPE) * size);

	for (i = 1; i < size; i++) {
		temp = list_sort[i];
		j = i - 1;
		while (temp < list_sort[j] && j >= 0)
			list_sort[j + 1] = list_sort[j--];

		list_sort[j + 1] = temp;
	}

	return list_sort;
}

static TYPE *select_sort_v1(TYPE list[], int size)
{
	int i, j;
	int min;
	TYPE *list_sort = (TYPE *)malloc(sizeof(TYPE) * size);

	memcpy(list_sort, list, sizeof(TYPE) * size);

	//low to high
	for (i = 0; i < size; i++) {
		min = i;
		for (j = i + 1; j < size; j++) {
			if (list_sort[j] < list_sort[min])
				min = j;
		}
		swap(list_sort + i, list_sort + min);
	}

	return list_sort;
}

//0 - 4
void quick_sort_v1(TYPE list[], int start, int end)
{
	int i, j;
	int base;

	if (start > end) {
		error("invalid parameter\n");
		exit(-1);
	}

	if (start == end)
		return;

	i = start;
	j = end;

	while (1) {
		do ++i;
		while (list[i] < list[start] && i <= end);
		do --j;
		while (list[j] > list[start] && j >= start);
		if (i < j)
			swap(list + i, list + j);
		else
			break;
	}
	swap(list + start, list + j);
	quick_sort_v1(list, start, j - 1);
	quick_sort_v1(list, j + 1, end);
}

void main()
{
	int i;
	TYPE a[5] = {4, 1, 3, 2, 5};
	TYPE *b;

	printf("select sort v1\n");
	b = select_sort_v1(a, 5);
	for (i = 0; i < 5; i++)
		printf("%d\n", *(b + i));

	printf("insert sort v1\n");
	b = insert_sort_v1(a, 5);
	for (i = 0; i < 5; i++)
		printf("%d\n", *(b + i));

	printf("original array\n");
	for (i = 0; i < 5; i++)
		printf("%d\n", *(a + i));

	printf("insert sort v1\n");
	b = insert_sort_v2(a, 5);
	for (i = 0; i < 5; i++)
		printf("%d\n", *(b + i));

	printf("original array\n");
	for (i = 0; i < 5; i++)
		printf("%d\n", *(a + i));

	printf("bubble sort v2\n");
	b = bubble_sort_v2(a, 5);
	for (i = 0; i < 5; i++)
		printf("%d\n", *(b + i));

	printf("quick sort v1\n");
	quick_sort_v1(a, 0, 4);
	for (i = 0; i < 5; i++)
		printf("%d\n", *(a + i));

	printf("bubble sort v1\n");
	bubble_sort_v1(a, 5);
	for (i = 0; i < 5; i++)
		printf("%d\n", *(a + i));

	exit(0);
}
