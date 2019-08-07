#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

static int THE_AGE = 37;
int THE_SIZE = 1000; // globals should not be directly accessible by other files
					//make getter and setter

int get_age()
{
	return THE_AGE;
}
void set_age(int age)
{
	THE_AGE = age;
}

double update_ratio(double new_ratio)
{
	static double ratio = 1.0; // bad! can be confusing and hard to find
	
	double old_ratio = ratio;
	ratio = new_ratio;
	
	return old_ratio;
}

void print_size()
{
	log_info("I think size is: %d", THE_SIZE);
}
