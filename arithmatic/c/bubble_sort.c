#include <stdio.h>
#include <stdlib.h>

//1 up
//0 down
void main(int argc, char *argv[])
{
//	int array[6] = {0, 5, 2, 3, 1, 4};
	int i, j, small;
	char order;
	int size;

	printf("Please enter the selected order:\n	- 1 up\n	- 0 down\n:");
	printf("Order:");
	order = getchar();

//add
	printf("Please enter array size:");
	scanf("%d", &size);

	int *array = NULL;
	array = malloc(size + 1);

	printf("Please enter number list which are need sorted:");
	for(i = 1; i < size + 1; i++)
		scanf("%d", array + i);

/*
	for (j = 5; j > 1; j--)
		for (i = 1; i < 5; i++) {
			if (order == '1') {
				if (array[i] > array[i+1]) {
					small = array[i+1];
					array[i+1] = array[i];
					array[i] = small;
				}
			}
			else if (order == '0') {
				if (array[i] < array[i+1]) {
					small = array[i+1];
					array[i+1] = array[i];
					array[i] = small;
				}
			}
			else {
				printf("The order para is wrong, just 0 or 1\n");
				goto End;
			}
		}
*/
	for (j = size; j > 1; j--)
		for (i = 1; i < size; i++) {
			if (order == '1') {
				if (array[i] > array[i+1]) {
					small = array[i+1];
					array[i+1] = array[i];
					array[i] = small;
				}
			}
			else if (order == '0') {
				if (array[i] < array[i+1]) {
					small = array[i+1];
					array[i+1] = array[i];
					array[i] = small;
				}
			}
			else {
				printf("The order para is wrong, just 0 or 1\n");
				goto End;
			}
	}

	for(i = 1; i < size + 1; i++)
		printf("%d ", array[i]);
	printf("\n");

End:
	printf("End\n");
}
