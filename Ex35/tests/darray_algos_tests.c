#include "minunit.h"
#include "darray_algos.h"
#include "darray.h"


int testcmp(const char** a, const char** b)
{
	return strcmp(*a, *b);
}

DArray* create_words()
{
	DArray* array = DArray_create(0, 5);
	char* words[] = { "asdfgss", "153las", "oioj", "werwar", "13234", "asdfgss" };
	
	for (int i = 0; i < 6; ++i) {
		DArray_push(array, words[i]);
	}
	
	return array;
}

int is_sorted(DArray* array)
{
	for (int i = 0; i < DArray_count(array) - 1; ++i) {
		if (strcmp(DArray_get(array, i), DArray_get(array, i + 1)) > 0) {
			return 0;
		}
	}
	
	return 1;
}

char* run_sort_test(int (*func) (DArray* da, DArray_compare), const char* name)
{
	DArray* test = create_words();
	mu_assert(!is_sorted(test), "array should not start sorted");
	
	debug("----- Testing %s -----", name);
	int rc = func(test, (DArray_compare) testcmp);
	mu_assert(rc == 0, "sorting failed");
	mu_assert(is_sorted(test), "array not sorted");
	
	DArray_destroy(test);
	
	return NULL;
}

char* test_qsort()
{
	run_sort_test(DArray_qsort, "quick sort");
	
	return NULL;
}

char* test_hsort()
{
	run_sort_test(DArray_hsort, "heap sort");
	
	return NULL;
}

char* test_msort()
{
	run_sort_test(DArray_msort, "merge sort");
	
	return NULL;
}

char* all_tests()
{
	mu_suite_start();

	mu_run_test(test_qsort);
	mu_run_test(test_msort);
	mu_run_test(test_hsort);
	
	return NULL;
}

RUN_TESTS(all_tests);
