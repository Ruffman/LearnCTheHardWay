#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count)
{
	log_info("count is: %d", count);
	
	if (count > 10) {
		int count = 100;
		
		log_info("count in this scope is: %d", count);
	}
	
	log_info("count is at exit: %d", count);
	
	count = 3000;
	
	log_info("count after assign: %d", count);
}

int main(int argc, char* argv[])
{
	log_info("age is currently: %d", get_age());
	
	set_age(100);
	
	log_info("age is now: %d", get_age());
	
	log_info("size is: %d", THE_SIZE);
	print_size();
	
	THE_SIZE = 199;
	
	log_info("size is now: %d", THE_SIZE);
	print_size();
	
	log_info("ratio at first: %f", update_ratio(2.0));
	log_info("ratio again: %f", update_ratio(10.0));
	log_info("ratio third time: %f", update_ratio(333.0));
	
	int count = 4;
	scope_demo(count);
	scope_demo(count * 20);
	
	log_info("count after calling scope_demo: %d", count);
	
	return 0;
}
