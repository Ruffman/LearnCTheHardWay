#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "dbg.h"

#define MAX_LINE_SIZE 256
#define MAX_NUM_LOGTYPES 128

enum mode {
	AND,
	OR
};

void die(char* text)
{
	printf("%s\n", text);
	exit(1);
}

int checkLognameForWords(char* curFileName, enum mode MODE, int argc, char* argv[])
{
	int wordsInName = 0;
	int word = 0;
	if (MODE == OR) {
		word = 2;
	} else {
		word = 1;
	}
	for ( ; word < argc; ++word) {
		if(strstr(curFileName, argv[word]) != NULL) {
			++wordsInName;
		}
		if(MODE == OR && wordsInName >= 1) {
			return 1;
		}
	}
	
	if (MODE == AND && wordsInName == (argc - 1)) {
		return 1;
	}
	
	return 0;
}

int main(int argc, char* argv[])
{
	enum mode MODE = AND;
	
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == 'o') {
				if (i > 1) {
					die("Please put -o as the second argument");
				}
				MODE = OR;
			}
		}
	}
	
	if (argc < 2) {
		die("You should enter a word to search for");
	} else if (MODE == OR && argc < 3) {
		die("You should enter a word to search for");
	}
	
	char* logFind = "/home/ruffman/.logfind";
	FILE* allowed = fopen(logFind, "r");
	if (!allowed) {
		die("Couldn't open file specifying allowed lognames");
	}
	char* line = malloc(MAX_LINE_SIZE);
	char* allowedLogs[MAX_NUM_LOGTYPES];
	
	int i = 0;
	while (fgets(line, sizeof(line), allowed)) {
		allowedLogs[i] = line;
		++i;
	}
	
	struct dirent* de = NULL;
	char* curFileName = NULL;
	
	DIR* curLoggingDir = opendir("/var/log");
	if (!curLoggingDir) {
		die("Couldn't open directory of log files");
	}
	
	int matchCount = 0;
	while ((de = readdir(curLoggingDir)) != NULL) {
		curFileName = de->d_name;
		
		int lc = checkLognameForWords(curFileName, MODE, argc, argv);
		
		if (lc == 1) {
			++matchCount;
			printf("%s\n", curFileName);
		}
	}
	printf("Found %d matching files\n", matchCount);
	
	fclose(allowed);
	closedir(curLoggingDir);
	free(line);
	
	return 0;
}
