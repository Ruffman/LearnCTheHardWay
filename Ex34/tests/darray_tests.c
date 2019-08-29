#include "minunit.h"
#include "darray.h"

static DArray* array = NULL;
static int* val1 = NULL;
static int* val2 = NULL;



char* test_create()
{
	array = DArray_create(sizeof(int), 100);
	mu_assert(array != NULL, "array creation failed");
	mu_assert(array->contents != NULL, "array contents are wrong");
	mu_assert(array->max == 100, "array max wrong");
	mu_assert(array->end == 0, "end is not correct");
	mu_assert(array->element_size == sizeof(int), "array element_size wrong");
	
	return NULL;
}

char* test_destroy()
{
	DArray_destroy(array);
	
	return NULL;
}

char* test_clear()
{
	DArray_clear(array);

	return NULL;
}

char* test_new()
{
	val1 = DArray_new(array);
	mu_assert(val1 != NULL, "failed to create new element 1");
	
	val2 = DArray_new(array);
	mu_assert(val2 != NULL, "failed to create new element 2");
	
	return NULL;
}

char* test_set()
{
	DArray_set(array, 0, val1);
	DArray_set(array, 1, val2);
	
	return NULL;
}

char* test_get()
{
	mu_assert(DArray_get(array, 0) == val1, "get failed 1");
	mu_assert(DArray_get(array, 1) == val2, "get failed 2");
	
	return NULL;
}

char* test_remove()
{
	int* val_check = DArray_remove(array, 0);
	mu_assert(val_check != NULL, "should not be NULL");
	mu_assert(*val_check == *val1, "wrong value while removing");
	mu_assert(DArray_get(array, 0) == NULL, "remove failed");
	free(val_check);
	
	val_check = DArray_remove(array, 1);
	mu_assert(val_check != NULL, "should not be NULL");
	mu_assert(*val_check == *val2, "wrong value while removing");
	mu_assert(DArray_get(array, 1) == NULL, "remove failed");
	free(val_check);
	
	return NULL;
}

char* test_expand_contract()
{
	int old_max = array->max;
	DArray_expand(array);
	mu_assert((unsigned int)array->max == old_max + array->expand_rate,
				"new array size is wrong");
	
	DArray_contract(array);
	mu_assert((unsigned int)array->max == array->expand_rate + 1,
				"should stay at least the size of expand_rate");
	
	DArray_contract(array);
	mu_assert((unsigned int)array->max == array->expand_rate + 1,
				"should stay at least the size of expand_rate");
	
	return NULL;
}

char* test_push_pop()
{
	for (int i = 0; i < 1000; ++i) {
		int* val = DArray_new(array);
		*val = i * 333;
		DArray_push(array, val);
	}
	
	mu_assert(array->max == 1201, "array wrong size");
	
	for (int i = 999; i >= 0; --i) {
		int* check = DArray_get(array, i);
		int* val = DArray_pop(array);
		mu_assert(val != NULL, "shouldn't be NULL");
		mu_assert(*val == *check, "popped wrong value");
		free(val);
	}
	
	return NULL;
}

char* all_tests()
{
	mu_suite_start();
	
	mu_run_test(test_create);
	mu_run_test(test_new);
	mu_run_test(test_set);
	mu_run_test(test_get);
	mu_run_test(test_remove);
	mu_run_test(test_clear);
	mu_run_test(test_expand_contract);
	mu_run_test(test_push_pop);
	mu_run_test(test_destroy);
	
	return NULL;
}

RUN_TESTS(all_tests);
