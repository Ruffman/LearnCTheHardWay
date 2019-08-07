#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dbg.h"

int normal_copy(char* from, char* to, int count)
{
	int i = 0;
	
	for (i = 0; i < count; ++i) {
		to[i] = from[i];
	}
	
	return i;
}

int duffs_device(char* from, char* to, int count)
{
	{
		int n = (count + 7) / 8;
		
		switch (count % 8) {
			case 0:
				do {
					*to++ = *from++;
					case 7:
					*to++ = *from++;
					case 6:
					*to++ = *from++;
					case 5:
					*to++ = *from++;
					case 4:
					*to++ = *from++;
					case 3:
					*to++ = *from++;
					case 2:
					*to++ = *from++;
					case 1:
					*to++ = *from++;
				} while (--n > 0);
		}
	}
	
	return count;
}

int zeds_device(char* from, char* to, int count)
{
	{
		int n = (count + 7) / 8;
		
		switch (count % 8) {
			case 0:
again:			*to++ = *from++;
			case 7:
				*to++ = *from++;
			case 6:
				*to++ = *from++;
			case 5:
				*to++ = *from++;
			case 4:
				*to++ = *from++;
			case 3:
				*to++ = *from++;
			case 2:
				*to++ = *from++;
			case 1:
				*to++ = *from++;
			if (--n > 0)
				goto again;
		}
	}
	
	return count;
}

int ruff_device(char* from, char* to, int count)
{
	for (int i = 0; i < count; ++i) {
		*to++ = *from++;
	}
	
	return count;
}

int valid_copy(char* data, int count, char expects)
{
	for (int i = 0; i < count; ++i) {
		if (data[i] != expects) {
			log_err("[%d] %c != %c", i, data[i], expects);
			return 0;
		}
	}
	
	return 1;
}

int main(int argc, char* argv[])
{
	char from[1001000] = { 'a' };
	char to[1001000] = { 'c' };
	int rc = 0;
	
	memset(from, 'x', 1001000);
	memset(to, 'y', 1001000);
	check(valid_copy(to, 1001000, 'y'), "Not initialized right");
	
	clock_t begin = clock();
	rc = normal_copy(from, to, 1001000);
	clock_t end = clock();
	log_info("normal copy speed: %.10f", (double)(end - begin) / CLOCKS_PER_SEC);
	check(rc == 1001000, "Normal copy failed: %d", rc);
	check(valid_copy(to, 1001000, 'x'), "Normal copy failed");
	
	memset(to, 'y', 1001000);
	
	begin = clock();
	rc = duffs_device(from, to, 1001000);
	end = clock();
	log_info("duff copy speed: %.10f", (double)(end - begin) / CLOCKS_PER_SEC);
	check(rc == 1001000, "Duffs device failed: %d", rc);
	check(valid_copy(to, 1001000, 'x'), "Duffs device failed");
	
	memset(to, 'y', 1001000);
	
	begin = clock();
	rc = zeds_device(from, to, 1001000);
	end = clock();
	log_info("zed copy speed: %.10f", (double)(end - begin) / CLOCKS_PER_SEC);
	check(rc == 1001000, "Zeds device failed: %d", rc);
	check(valid_copy(to, 1001000, 'x'), "Zeds device failed");
	
	memset(to, 'y', 1001000);
	
	begin = clock();
	rc = ruff_device(from, to, 1001000);
	end = clock();
	log_info("ruff copy speed: %.10f", (double)(end - begin) / CLOCKS_PER_SEC);
	check(rc == 1001000, "Ruff device failed: %d", rc);
	check(valid_copy(to, 1001000, 'x'), "Ruff device failed");
	
	return 0;
	
error:
	return 1;
}
