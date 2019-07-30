#include <stdio.h>

int main(int argc, char* argv[])
{
	int areas[] = { 1, 2, 3, 4, 5 };
	char name[] = "Zed";
	char full_name[] = { 'Z', 'e', 'd', ' ', 'A',
						 '.', ' ', 'S', 'h', 'a', 'w', '\0' };
						 
	printf("Size of an int: %ld\n", sizeof(int));
	printf("Size of areas: %ld\n", sizeof(areas));
	printf("Ints in areas: %ld\n", sizeof(areas) / sizeof(int));
	printf("Size of a char: %ld\n", sizeof(char));
	printf("Size of name: %ld\n", sizeof(name));
	printf("Size of full_name: %ld\n", sizeof(full_name));
	
	printf("Name: \"%s\"\nFull_name: \"%s\"\n", name, full_name);
	
	return 0;
}
