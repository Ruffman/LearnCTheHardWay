#include <stdio.h>

int main(int argc, char* argv[])
{
	if(argc < 2) {
		printf("Not enough arguments!\n");
	} else if (argc > 1 && argc <= 4) {
		printf("Your arguments :\n");
		
		for(int i = 0; i < argc; ++i) {
			printf("%s ", argv[i]);
		}

		printf("\n");
	} else {
		printf("You have too many arguments\n");
	}

	return 0;
}
