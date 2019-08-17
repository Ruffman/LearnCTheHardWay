#include "minunit.h"
#include "lcthw/list.h"
#include <assert.h>

static List* list = NULL;
static List* list2 = NULL;
static List* list3 = NULL;
char* test1 = "test1 data";
char* test2 = "test2 data";
char* test3 = "test3 data";

char* test_create()
{
	list = List_create();
	mu_assert(list != NULL, "Failed to create list");
	
	return NULL;
}

char* test_destroy()
{
	List_clear_destroy(list);
	
	return NULL;
}

char* test_push_pop()
{
	List_push(list, test1);
	mu_assert(List_last(list) == test1, "Wrong last item");
	
	List_push(list, test2);
	mu_assert(List_last(list) == test2, "Wrong last item");
	
	List_push(list, test3);
	mu_assert(List_last(list) == test3, "Wrong last item");
	mu_assert(List_count(list) == 3, "Wrong item count on push");
	
	char* val = List_pop(list);
	mu_assert(val == test3, "Wrong value on pop");
	
	val = List_pop(list);
	mu_assert(val == test2, "Wrong value on pop");
	
	val = List_pop(list);
	mu_assert(val == test1, "Wrong value on pop");
	mu_assert(List_count(list) == 0, "Wrong item count on pop");
	
	return NULL;
}

char* test_unshift()
{
	List_unshift(list, test1);
	mu_assert(List_first(list) == test1, "Wrong first item");
	
	List_unshift(list, test2);
	mu_assert(List_first(list) == test2, "Wrong first item");
	
	List_unshift(list, test3);
	mu_assert(List_first(list) == test3, "Wrong first item");
	mu_assert(List_count(list) == 3, "Wrong item count after unshift");
	
	return NULL;
}

char* test_copy()
{
	list2 = List_copy(list);
	mu_assert(List_first(list2) == test3, "Wrong first item");
	mu_assert(list2->first->next->value == test2, "Wrong second item");
	mu_assert(List_last(list2) == test1, "Wrong last item");
	mu_assert(List_count(list2) == 3, "Wrong item count");

	return NULL;
}

char* test_remove()
{
	// we only test middle case, since the other cases are covered by pop and shift
	char* var = List_remove(list, list->first->next);
	mu_assert(var == test2, "Wrong value on remove");
	mu_assert(List_first(list) == test3, "Wrong first item after remove");
	mu_assert(List_last(list) == test1, "Wrong last item after remove");
	mu_assert(List_count(list) == 2, "Wrong item count after remove");
	
	return NULL;
}

char* test_shift()
{
	char* var = List_shift(list);
	mu_assert(var == test3, "Wrong value on shift");
	
	var = List_shift(list);
	mu_assert(var == test1, "Wrong value on shift");
	mu_assert(List_count(list) == 0, "Wrong item count after shift");
	
	return NULL;
}

char* test_join()
{
	List_push(list, test1);
	List_push(list, test2);
	list3 = List_join(list2, list);
	mu_assert(List_first(list3) == test3, "Wrong first item after joining");
	mu_assert(List_last(list3) == test2, "Wrong last item after joining");
	mu_assert(List_count(list3) == 5, "Wrong element count after joining");

	return NULL;
}

char* all_tests()
{
	mu_suite_start();
	
	mu_run_test(test_create);
	mu_run_test(test_destroy);
	mu_run_test(test_push_pop);
	mu_run_test(test_unshift);
	mu_run_test(test_copy);
	mu_run_test(test_remove);
	mu_run_test(test_shift);
	mu_run_test(test_join);
	
	return NULL;
}

RUN_TESTS(all_tests);

