#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char* name;
	int age;
	int height;
	int weight;
};

struct Person create_person(char* name, int age, int height, int weight)
{
	// allocate memory for the size of our struct
	struct Person who;
	
	who.name = name;
	who.age = age;
	who.height = height;
	who.weight = weight;
	
	return who;
}

void print_person(struct Person who)
{
	printf("Name: %s\n", who.name);
	printf("Age: %d\n", who.age);
	printf("Height: %d\n", who.height);
	printf("Weight: %d\n", who.weight);
}

int main(int argc, char* argv[])
{
	struct Person joe = create_person("Joe Frank", 45, 159, 66);
	struct Person matt = create_person("Matt Dink", 22, 197, 63);
	
	
	print_person(joe);
	print_person(matt);
	
	return 0;
}
