#include "darray_algos.h"
#include <stdlib.h>



int DArray_qsort(DArray* array, DArray_compare cmp)
{
	qsort(array->contents, DArray_count(array), sizeof(void*), cmp);
	
	return 0;
}

static inline void merge(void* content, int l, int m, int r, DArray_compare cmp)
{
	int i, j, k = 0;
	int n1 = m - l + 1;
	int n2 = r - m;
	
	void* left = calloc(m - l + 1, sizeof(void*));
	void* right = calloc(r - m, sizeof(void*));
	
	for (i = 0; i < n1; ++i) {
		left[i] = content[l + i];
	}
	for (j = 0; j < n2; ++j) {
		right[i] = content[m + 1 + i];
	}
	
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (cmp) {
			content[k] = left[i++];
		} else {
			content[k] = right[j++];
		}
		k++;
	}
	
	while (i < n1) {
		content[k++] = left[i++];
	}
	while (j < n2) {
		content[k++] = right[j++];
	}
}

static inline void mergeSort(void* content, int left, int right, DArray_compare cmp)
{
	if (right > left) {
		int middle = (left + right) / 2;
		
		mergeSort(content, left, middle, cmp);
		mergeSort(content, middle + 1, right, cmp);
		merge(content, left, middle, right, cmp);
	}
}

int DArray_msort(DArray* array, DArray_compare cmp)
{
	mergeSort(array->contents, 0, array->end, cmp);
	
	return 0;//mergesort(array->contents, DArray_count(array), sizeof(void*), cmp);
}

int DArray_hsort(DArray* array, DArray_compare cmp)
{
	return 0;//heapsort(array->contents, DArray_count(array), sizeof(void*), cmp);
}	
