#include <stdio.h>
#include <ctype.h>
#include "dbg.h"

int print_a_message(const char* msg, int strlen)
{
	printf("A STRING: %s\n", msg);
	
	return 0;
}

int uppercase(const char* msg, int strlen)
{
	for (int i = 0; i < strlen; ++i) {
		printf("%c", toupper(msg[i]));
	}
	printf("\n");
	
	return 0;
}

int lowercase(const char* msg, int strlen)
{
	for (int i = 0; i < strlen; ++i) {
		printf("%c", tolower(msg[i]));
	}
	printf("\n");
	
	return 0;
}

int fail_on_purpose(const char* msg, int strlen)
{
	return 1;
}
