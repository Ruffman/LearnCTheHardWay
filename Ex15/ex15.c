#include <stdio.h>

int main(int argc, char* argv[])
{
	int ages[] = { 23, 43, 12, 89, 2 };
	char* names[] = { "Allan", "Ritchy", "Slurp", "Derp", "Ricky" };
	
	int count = sizeof(ages) / sizeof(int);
	
	for (int i = 0; i < count; ++i) {
		printf("%s is %d years alive\n", names[i], ages[i]); // danger if both 															arrays are not same size
	}
	
	printf("--------\n");
	
	int* cur_age = ages;
	*cur_age = 33;
	*(++cur_age) = 52;
	--cur_age;
	cur_age[2] = 37;
	char** cur_name = names;
	*cur_name = "Rosetta";
	
	// pointer arithmatic, dangerous
	for (int i = 0; i < count; ++i) {
		printf("%s is %d years old\n", *(cur_name + i), *(cur_age + i));
	}
	
	printf("--------\n");
	
	// pretend pointers are arrays. Safe way!
	for (int i = 0; i < count; ++i) {
		printf("%s is %d years old again\n", cur_name[i], cur_age[i]);
	}
	
	printf("--------\n");
	
	// very complex way
	for (cur_name = names, cur_age = ages; (cur_age - ages) < count; 
		++cur_name, ++cur_age) {
		printf("%s has lived %d years\n", *cur_name, *cur_age);
	}
	
	return 0;
}
