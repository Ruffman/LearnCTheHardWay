#ifndef darray_algos_h
#define darray_algos_h

#include "darray.h"



typedef int (*DArray_compare) (const void* a, const void* b);

void DArray_qsort(DArray* array, DArray_compare cmp);

int DArray_msort(DArray* array, DArray_compare cmp);

int DArray_hsort(DArray* array, DArray_compare cmp);

#endif

