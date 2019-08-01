#include <stdio.h>

int main(int argc, char* argv[])
{
	char* names[] = { "Bob", "Durd", "Pleb", "Swoosh" };
	
	// different size of strings doesn't matter since char* can point to
	// a string of any length or NULL
	for(int i = 0; i < sizeof(names) / sizeof(names[0]); ++i) {
		printf("%d: %s\n", i+1, names[i]);
	}
	
	for(int i = 1; i < argc; ++i) {
		printf("%d: %s\n", i+1, argv[i]);
	}
	
	return 0; 
}

