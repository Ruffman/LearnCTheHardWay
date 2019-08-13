#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dbg.h"

int main(int argc, char* argv[])
{
	bool MODE_AND = true;
	
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == 'o') {
				MODE_AND = false;
			}
		}
	}
	
	char* logFind = "~/.logfind";
	FILE* allowed = fopen(logFind, "r");
	char* line = malloc(256);
	// char* allowedFiles[];
	
	while (fgets(line, sizeof(line), allowed)) {
		printf("%s", line);
	}
	
	if (MODE_AND) {
		
	}
	
	fclose(allowed);
	free(line);
	
	return 0;
}
