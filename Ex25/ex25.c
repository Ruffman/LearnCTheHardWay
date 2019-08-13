#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char** out_string, int max_buffer)
{
	*out_string = calloc(1, max_buffer + 1);
	check_mem(*out_string);
	
	char* result = fgets(*out_string, max_buffer, stdin);
	check(result != NULL, "Input error");
	
	return 0;
error:
	if (*out_string) free(*out_string);
	*out_string = NULL;
	return -1;
}

int read_int(long* out_int)
{
	char* input = NULL;
	char* end = NULL;
	int rc = read_string(&input, MAX_DATA);
	check(rc == 0, "Failed to read number");
	
	*out_int = strtol(input, &end, 10);
	check((*end == '\0' || *end == '\n') && 
			*input != '\0', "Invalid number: %s", input);
			
	free(input);
	
	return 0;
error:
	if (input) free(input);
	return -1;
}

int read_scan(const char* fmt, ...)
{
	int rc = 0;
	long* out_int = NULL;
	char* out_char = NULL;
	char** out_string = NULL;
	int max_buffer = 0;
	
	va_list argp;
	va_start(argp, fmt);
	
	for (int i = 0; fmt[i] != '\0'; ++i) {
		if (fmt[i] == '%') {
			++i;
			switch (fmt[i]) {
				case '\0':
					sentinel("Invalid format, you ended with %%");
					break;
				case 'd':
					out_int = va_arg(argp, long*);
					rc = read_int(out_int);
					check(rc == 0, "Failed to read int");
					break;
				case 'c':
					out_char = va_arg(argp, char*);
					*out_char = fgetc(stdin);
					break;
				case 's':
					max_buffer = va_arg(argp, int);
					out_string = va_arg(argp, char**);
					rc = read_string(out_string, max_buffer);
					check(rc == 0, "Failed to read string");
					break;
				default:
					sentinel("Invalid format");
			}
		} else {
			fgetc(stdin);
		}
		
		check(!feof(stdin) && !ferror(stdin), "Input error");
	}
	
	va_end(argp);
	
	return 0;
error:
	va_end(argp);
	return -1;
}

int print_out(const char* fmt, ...)
{
	int pc = 0;
	va_list argp;
	va_start(argp, fmt);
	int print_int = 0;
	char print_char = ' ';
	char* print_string = NULL;
	// double print_double = 0.0;
	
	for (int i = 0; fmt[i] != '\0'; ++i) {
		if (fmt[i] == '%') {
			++i;
			switch (fmt[i]) {
				case '\0':
					sentinel("Wrong input format");
					break;
				case 'd':
					print_int = va_arg(argp, int);
					int length = snprintf(NULL, 0, "%d", print_int);
					print_string = malloc(length + 1);
					snprintf(print_string, length + 1, "%d", print_int);
					pc = fputs(print_string, stdout);
					check(pc != -1, "Failed to print int");
					free(print_string);
					break;
				case 'c':
					print_char = va_arg(argp, int);
					pc = putchar(print_char);
					check(pc != -1, "Failed to print char");
					break;
				case 's':
					print_string = va_arg(argp, char*);
					pc = fputs(print_string, stdout);
					check(pc != -1, "Failed to print string");
					break;
				case 'f':
					log_info("Not yet supported");
					break;
				default:
					sentinel("reached default in switch in print_out");
			}
		} else {
			putchar(fmt[i]);
		}
		

	}
	
	va_end(argp);
	
	return 0;
error:
	va_end(argp);
	return -1;
}

int main(int argc, char* argp[])
{
	char* first_name = NULL;
	char initial = ' ';
	char* last_name = NULL;
	long age = 0;
	
	printf("What's your first name? ");
	int rc = read_scan("%s", MAX_DATA, &first_name);
	check(rc == 0, "Failed first name");
	
	printf("What's your intitial? ");
	rc = read_scan("%c\n", &initial);
	check(rc == 0, "Failed initial");
	
	printf("What's your last name? ");
	rc = read_scan("%s", MAX_DATA, &last_name);
	check(rc == 0, "Failed last name");
	
	printf("What's your age? ");
	rc = read_scan("%d", &age);
	check(rc == 0, "Failed age");
	
	print_out("-----------RESULTS-----------\n");
	print_out("First name: %s", first_name);
	print_out("Initial: %c\n", initial);
	print_out("Last name: %s", last_name);
	print_out("Age: %d\n", age);
	
	free(first_name);
	free(last_name);
	
	return 0;
error:
	return -1;
}
