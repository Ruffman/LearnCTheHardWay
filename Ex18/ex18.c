#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include "dbg.h"



typedef int (*compare_cb)(int a, int b);

int* bubble_sort(int* numbers, int count, compare_cb cmp)
{
	assert(numbers != NULL && "Received invalid argument");
	
	int temp = 0;
	int i = 0;
	int j = 0;
	int* target = malloc(count * sizeof(int));
	check_mem(target);
	
	memcpy(target, numbers, count * sizeof(int));
	
	for (i = 0; i < count; ++i) {
		for (j = 0; j < count - 1; ++j) {
			if (cmp(target[j], target[j + 1]) > 0) {
				temp = target[j + 1];
				target[j + 1] = target[j];
				target[j] = temp;
			}
		}
	}
	
	return target;
error:
	if (target) free(target);
	return NULL;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int strange_order(int a, int b)
{
	if (a == 0 || b == 0) {
		return 0;
	} else {
		return a % b;
	}
}

void test_sorting(int* numbers, int count, compare_cb cmp)
{
	assert(numbers != NULL && "Received invalid argument");
	int* sorted = bubble_sort(numbers, count, cmp);
	check(sorted != NULL, "Sorting error in test_sorting");
	
	for (int i = 0; i < count; ++i) {
		printf("%d, ", sorted[i]);
	}
	
	printf("\n");
	
	free(sorted);
	return;
error:
	if (sorted) free(sorted);
}

int main(int argc, char* argv[])
{
	assert(argc >= 2 && "Usage: ./ex18 2 4 6 1 4 8 3 7");
	
	int count = argc - 1;
	int* numbers = malloc(count * sizeof(int));
	check_mem(numbers);
	
	for (int i = 0; i < count; ++i) {
		numbers[i] = atoi(argv[i + 1]);
	}
	
	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);
	
	free(numbers);
	
	return 0;
error:
	if (numbers) free(numbers);
	return 1;
}

