#include <stdio.h>
#include <ctype.h>

int can_print_it(char c);
void print_letters(char arg[]);

void print_arguments(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i) {
		print_letters(argv[i]);
	}
}

void print_letters(char arg[])
{
	for (int i = 0; arg[i] != '\0'; ++i) {
		char ch = arg[i];
		
		if(can_print_it(ch)) {
			printf("'%c' == %d ", ch, ch);
		}
	}
	
	printf("\n");
}

int can_print_it(char ch)
{
	// those functions are part of ctype.h
	// they evaluate if given char is in the alphabet or a blank space
	// and return 0 if it is not of the evaluated class
	return isalpha(ch) || isblank(ch) || isdigit(ch);
}

int main(int argc, char* argv[])
{
	print_arguments(argc, argv);
	return 0;
}
