#include "minunit.h"
#include <dlfcn.h>



typedef int (*lib_function)(const char* data, int data_length);
char* lib_file = "build/ex30lib.so";
void* lib = NULL;

int check_function(const char* func_to_run, const char* data, int data_length, 
					int expected)
{
	lib_function func = dlsym(lib, func_to_run);
	check(func != NULL, "Did not find function %s in the library %s: %s",
											func_to_run, lib_file, dlerror());
	
	int rc = func(data, data_length);
	check(rc == expected, "Function %s return %d for data: %s",
							func_to_run, rc, data);
	
	return 1;
error:
	return 0;
}
char* test_dlopen()
{
	lib = dlopen(lib_file, RTLD_NOW);
	mu_assert(lib != NULL, "Failed to open library");
	return NULL;
}

char* test_functions()
{
	mu_assert(check_function("print_a_message", "Hello", 5, 0), 								"print_a_message failed");
	mu_assert(check_function("uppercase", "hello", 5, 0),
								"uppercase failed");
	mu_assert(check_function("lowercase", "HeLLo", 5, 0),
								"lowercase failed");
	return NULL;
}

char* test_failures()
{
	mu_assert(check_function("fail_on_purpose", "Hello", 5, 1), 
								"fail_on_purpose should fail");
	return NULL;
}

char* test_dlclose()
{
	int rc = dlclose(lib);
	mu_assert(rc == 0, "Failed to close the library");
	return NULL;
}

char* all_tests()
{
	mu_suite_start();
	
	mu_run_test(test_dlopen);
	mu_run_test(test_functions);
	mu_run_test(test_failures);
	mu_run_test(test_dlclose);
	
	return NULL;
}

RUN_TESTS(all_tests);

