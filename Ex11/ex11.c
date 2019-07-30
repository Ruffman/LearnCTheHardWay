#include <stdio.h>

int main(int argc, char* argv[])
{
	int numbers[4] = { 0, 5, 3, 7 };
	// char name[4] = { 'a' }; C initializes the rest of the string with nul
	char name[4] = { 'a', 'b', 'c', 'd' }; // not terminated by nul, danger
		
	printf("numbers: %d, %d, %d, %d\n", numbers[0], numbers[1],
									 numbers[2], numbers[3]);
	printf("name: %c, %c, %c, %c\n", name[0], name[1], name[2], name[3]);
	
	printf("%s\n", name);
	
	numbers[0] = 1;
	numbers[1] = 2;
	numbers[2] = 3;
	numbers[3] = 4;
	
	name[0] = 'Z';
	name[1] = 'e';
	name[2] = 'd';
	// name[3] = '\0'; // nul_byte to terminate a string in C
	name[3] = 'A'; // whoops, another bug

	printf("numbers assigned: %d, %d, %d, %d\n", numbers[0], numbers[1],
												numbers[2], numbers[3]);
	
	numbers[0] = 'Z';
	numbers[1] = 'e';
	numbers[2] = 'd';
	numbers[3] = '\0';
	
	printf("numbers with char: %d, %d, %d, %d\n", numbers[0], numbers[1],
											 numbers[2], numbers[3]);

	printf("name assigned: %c, %c, %c, %c\n", name[0], name[1], name[2], name[3]);
	
	printf("name as int: %i, %i, %i, %i\n", name[0], name[1], name[2], name[3]);
	
	printf("again: %s\n", name);
	
	char* another = "Ello";
	
	printf("another way: %s\n", another);
	
	printf("numbers assigned: %c, %c, %c, %c\n", another[0], another[1],
											 another[2], another[3]);

	return 0;
}
