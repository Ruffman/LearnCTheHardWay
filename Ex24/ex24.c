#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
	BLUE_EYES, GREEN_EYES, BROWN_EYES,
	BLACK_EYES, OTHER_EYES
} EyeColor;

const char* EYE_COLOR_NAMES[] = {
	"Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
	int age;
	char first_name[MAX_DATA];
	char last_name[MAX_DATA];
	EyeColor eyes;
	float income;
} Person;

void remove_newline_space(char* string)
{
	int count = 0;
	for (int i = 0; i < strlen(string); ++i) {
		char current = string[i];
		if ((current == ' ') || (current == '\n')) {
			continue;
		}
		string[count++] = current;
	}
	string[count] = '\0';
}

int main(int argc, char* argv[])
{
	Person you = { .age = 0 };
	char* in = NULL;
	char buffer[MAX_DATA];
	
	printf("What's your First Name? ");
	in = fgets(buffer, MAX_DATA - 1, stdin);
	check(in != NULL, "Failed to read first name");
	remove_newline_space(buffer);
	memcpy(you.first_name, buffer, strlen(buffer));
	
	printf("Whats's your Last Name? ");
	in = fgets(buffer, MAX_DATA - 1, stdin);
	check(in != NULL, "Failed to read last name");
	remove_newline_space(buffer);
	memcpy(you.last_name, buffer, strlen(buffer));
	
	printf("How old are you? ");
	in = fgets(buffer, MAX_DATA - 1, stdin);
	check(in != NULL, "Failed to read age or not a number");
	you.age = atoi(buffer);
	
	printf("What's your eye color?\n");
	for (int i = 0; i <= OTHER_EYES; ++i) {
		printf("%d: %s\n",i + 1, EYE_COLOR_NAMES[i]);
	}
	
	in = fgets(buffer, MAX_DATA - 1, stdin);
	check(in != NULL, "Failed to read eye color or not a number");
	int eyeColor = atoi(buffer);
	
	you.eyes = eyeColor - 1;
	check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Wrong eye color specified");
	
	printf("How much do you make per hour? ");
	in = fgets(buffer, MAX_DATA - 1, stdin);
	check(in != NULL, "Failed to read income or not a float");
	you.income = atoi(buffer);
	
	printf("------------RESULTS------------\n");
	
	printf("First name: %s\n", you.first_name);
	printf("Last name: %s\n", you.last_name);
	printf("Your age: %d\n", you.age);
	printf("Your eye color: %s\n", EYE_COLOR_NAMES[you.eyes]);
	printf("Hourly income: %f\n", you.income);
	
	return 0;
	
error:
	return -1;
}
