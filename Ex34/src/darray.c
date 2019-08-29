#include "darray.h"
#include "dbg.h"
#include <assert.h>

DArray* DArray_create(size_t element_size, size_t initial_max)
{
	DArray* array = malloc(sizeof(DArray));
	check_mem(array);
	
	array->contents = calloc(initial_max, sizeof(void*));
	check_mem(array->contents);
	
	array->end = 0;
	array->max = initial_max;
	check(array->max > 0, "You have to set the size to bigger than 0");
	
	array->element_size = element_size;
	array->expand_rate = DEFAULT_EXPAND_RATE;
	
	return array;
error:
	if (array->contents) free(array->contents);
	if (array) free(array);
	
	return NULL;
}

void DArray_destroy(DArray* array)
{
	check(array != NULL, "invalid argument pointer");
	if (array->contents) {
		free(array->contents);
	}
	free(array);
error:
	return;
}

void DArray_clear(DArray* array)
{
	check(array != NULL, "invalid argument pointer");
	if (array->element_size > 0) {
		for (int i = 0; i < array->max; ++i) {
			if (array->contents[i] != NULL) {
				free(array->contents[i]);
			}
		}
	}
error:
	return;
}

void DArray_clear_destroy(DArray* array)
{
	check(array != NULL, "invalid argument pointer");
	DArray_clear(array);
	DArray_destroy(array);
error:
	return;
}

static inline int DArray_resize(DArray* array, size_t newSize)
{
	array->max = newSize;
	debug("%d array max", array->max);
	check(array->max > 0, "darray has to be bigger than 0");
	
	void* contents = realloc(array->contents, array->max * sizeof(void*));
	check_mem(contents);
	
	array->contents = contents;
	
	return 0;
error:
	return -1;
}

int DArray_expand(DArray* array)
{
	size_t newSize = array->max + array->expand_rate;
	check(DArray_resize(array, newSize) == 0, "resizing the array failed");
	
	return 0;
error:
	return -1;
}

int DArray_contract(DArray* array)
{
	size_t newSize = array->end < (int)array->expand_rate ? 
						(int)array->expand_rate : array->end;
	check(DArray_resize(array, newSize + 1) == 0, "resizing array failed");
	
	return 0;
error:
	return -1;
}

int DArray_push(DArray* array, void* el)
{
	check(array != NULL, "invalid argument pointer");
	check(el != NULL, "invlaid element");
	
	if (array->end + 1 == array->max) {
		check(DArray_expand(array) == 0, "failed to push array");
	}
	array->contents[array->end++] = el;
	
	return 0;
error:
	return -1;
}

void* DArray_pop(DArray* array)
{
	check(array != NULL, "invalid argument pointer");
	check(array->end - 1 >= 0, "can't pop from empty array");
	
	array->end--;
	void* el = DArray_remove(array, array->end);
	
	check(el != NULL, "should not be NULL");
	check(DArray_contract(array) == 0, "Failed to pop array");
	
	return el;
error:
	return NULL;
}

