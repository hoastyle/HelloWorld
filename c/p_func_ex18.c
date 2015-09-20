#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "output.h"

/*Compare function*/
typedef int (*compare_cb)(int a, int b);

/*Sort algorithm function*/
typedef int *(*sort)(int *numbers, int count, compare_cb cmp);

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int max, temp;
	int i = 0, j = 0;
	int *target = NULL;

	target = malloc(sizeof(int) * count);
	if(!target)
		die("Memory err\n");
	
	memcpy(target, numbers, sizeof(int) * count);
	max = target[0];
	for(i = 0; i < count; i++){
		debug("target[i] is %d\n", target[i]);
	}

	for(i = 0; i < count; i++) {
		for(j = 0; j < count - 1; j++){
			if(cmp(target[j], target[j+1]) > 0) {
				temp = target[j+1];
				target[j+1] = target[j];
				target[j] = temp;
			}
		}
	}

	return target;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

void test_sorting(int *numbers, int count, compare_cb cmp, sort sort)
{
    int i = 0;
    //int *sorted = bubble_sort(numbers, count, cmp);
    int *sorted = sort(numbers, count, cmp);

    if(!sorted) die("Failed to sort as requested.");

    for(i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);
}

int main(int argc, char *argv[])
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if(!numbers) die("Memory error.");

    for(i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, sorted_order, bubble_sort);
	test_sorting(numbers, count, reverse_order, bubble_sort);
    //test_sorting(numbers, count, strange_order, sort);

    free(numbers);

    return 0;
}
