#include <stdio.h>
#include <ctype.h>
#include <string.h>


void print_letters(char arg[], int argl);

void print_arguments(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i) {
		int length = strlen(argv[i]);
		print_letters(argv[i], length);
	}
}

void print_letters(char arg[], int argl)
{
	for (int i = 0; i < argl; ++i) {
		char ch = arg[i];
		
		// those functions are part of ctype.h
		// they evaluate if given char is in the alphabet or a blank space
		// and return 0 if it is not of the evaluated class
		if(isalpha(ch) || isblank(ch) || isdigit(ch)) {
			printf("'%c' == %d ", ch, ch);
		}
	}
	
	printf("\n");
}

int main(int argc, char* argv[])
{
	print_arguments(argc, argv);
	return 0;
}
