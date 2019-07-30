#include "stdio.h"

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Not enough function arguments!\n");
	}
	
	for(int w = 1; w < argc; ++w) {
		for(int i = 0; argv[w][i] != '\0'; ++i) {
			char c = argv[w][i];
			printf("%c\n", c);
			
			if(c < 91) {
				c += 32;
			}
			
			switch(c) {
				case 'a':
					printf("%d: %c is a vowel!\n", i, c);
					break;
				case 'e':
					printf("%d: %c is a vowel!\n", i, c);
					break;
				case 'i':
					printf("%d: %c is a vowel!\n", i, c);
					break;
				case 'o':
					printf("%d: %c is a vowel!\n", i, c);
					break;
				case 'u':
					printf("%d: %c is a vowel!\n", i, c);
					break;
				default:
					printf("%d: %c is not a vowel!\n", i, c);
			}
		}
	}
	
	return 0;
}
