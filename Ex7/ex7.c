#include <stdio.h>

int main(int argc, char* argv[])
{
	int distance = 100;
	float power = 2.345f;
	double super_power = 56789.4532;
	char initial = 'A';
	char first_name[] = "Zed";
	char last_name[] = "Shaw";

	// array is of size 4 bc in C the end of strings is a nul_byte.
	// overwriting this causes bad things
	first_name[3] = 'Z';

	printf("You are %d miles away\n", distance);
	printf("You have %f levels of power\n", power);
	printf("You have %f levels of awesome super-power\n", super_power);
	printf("I have a first name %s.\n", first_name+100);
	printf("I have a last name %s.\n", last_name);
	printf("My whole name is %s %c %s.\n", first_name, initial, last_name);

	
	int bugs = 100;
	double bug_rate = 1.2;

	printf("You have %d bugs at the imaginary rate of %f.\n", bugs, bug_rate);
	
	// too long for long resulting in an overflow
	long universe_of_defects = 1L * 1024L * 1024L * 1024L * 1024L * 1024L * 1024L
		* 1024L;
	printf("The entire universe has %ld bugs.\n", universe_of_defects);

	unsigned long universe_of_unsigned = 1L * 1024L * 1024L * 1024L * 1024L * 1024L
			* 1024L;
	printf("unsigned %ld bugs.\n", universe_of_unsigned);

	double expected_bugs = bugs * bug_rate;
	printf("You are expected to have %f bugs.\n", expected_bugs);

	double part_of_universe = expected_bugs / universe_of_defects;
	printf("That is only a %e portion of the universe.\n", part_of_universe);

	char nul_byte = '\0';
	int care_percentage = bugs * nul_byte;
	// printing a int to a string format is no bueno
	printf("C is weird, check it out: %s%%.\n", care_percentage);

	return 0;
}
