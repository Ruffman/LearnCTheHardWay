#include "darray_algos.h"
#include <stdlib.h>



int DArray_qsort(DArray* array, DArray_compare cmp)
{
	qsort(array->contents, DArray_count(array), sizeof(void*), cmp);
	
	return 0;
}

int DArray_msort(DArray* array, DArray_compare cmp)
{
	return 0;//mergesort(array->contents, DArray_count(array), sizeof(void*), cmp);
}

int DArray_hsort(DArray* array, DArray_compare cmp)
{
	return 0;//heapsort(array->contents, DArray_count(array), sizeof(void*), cmp);
}	
