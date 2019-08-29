#include "minunit.h"
#include "darray_algos.h"
#include "darray.h"


int char_compare(const char** a, const char** b)
{
	return stringcmp(*a, *b);
}

DArray* create_words()
{
	DArray* array = DArray_create(sizeof(char)
}
