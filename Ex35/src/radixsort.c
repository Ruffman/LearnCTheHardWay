#include "radixsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dbg.h"

RadixMap* RadixMap_create(size_t max)
{
	check(max > 0, "RadixMap needs to be bigger than 0");
	
	RadixMap* map = calloc(1, sizeof(RadixMap));
	check_mem(map);
	
	map->contents = calloc(max + 1, sizeof(RMElement));
	check_mem(map->contents);
	
	map->temp = calloc(max + 1, sizeof(RMElement));
	check_mem(map->temp);
	
	map->max = max;
	map->end = 0;
	
	return map;
error:
	if (map->contents) free(map->contents);
	if (map->temp) free(map->temp);
	if (map) free(map);
	return NULL;
}

void RadixMap_destroy(RadixMap* map)
{
	check(map != NULL, "Invalid function parameter RadixMap*");
	
	free(map->contents);
	free(map->temp);
	free(map);
	
error:
	return;
}

#define ByteOf(x, y) (((uint8_t*) x)[(y)])

static inline void radix_sort(short offset, uint64_t max, 
								uint64_t* source, uint64_t* dest)
{
	uint64_t count[256] = { 0 };
	uint64_t* cp = NULL;
	uint64_t* sp = NULL;
	uint64_t* end = NULL;
	uint64_t s = 0;
	uint64_t c = 0;
	
	for (sp = source, end = source + max; sp < end; ++sp) {
		count[ByteOf(sp, offset)]++;
	}
	
	for (s = 0, cp = count, end = count + 256; cp < end; ++cp) {
		c = *cp;
		*cp = s;
		s += c;
	}
	
	for (sp = source, end = source + max; sp < end; ++sp) {
		cp = count + ByteOf(sp, offset);
		dest[*cp] = *sp;
		++(*cp);
	}
}

void RadixMap_sort(RadixMap* map)
{
	uint64_t* source = &map->contents[0].raw;
	uint64_t* temp = &map->temp[0].raw;
	
	radix_sort(0, map->end, source, temp);
	radix_sort(1, map->end, temp, source);
	radix_sort(2, map->end, source, temp);
	radix_sort(3, map->end, temp, source);
}

RMElement* RadixMap_find(RadixMap* map, uint32_t to_find)
{
	int low = 0;
	int high = map->end - 1;
	RMElement* data = map->contents;
	
	while (low <= high) {
		int middle = low + (high - low) / 2;
		uint32_t key = data[middle].data.key;
		
		if (to_find < key) {
			high = middle - 1;
		} else if (to_find > key) {
			low = middle + 1;
		} else {
			return &data[middle];
		}
	}
	
	log_info("%d;%d", low, high);
	return NULL;
}
int RadixMap_add(RadixMap* map, uint32_t key, uint32_t value)
{
	check(key < UINT32_MAX, "Key can't be equal to UINT32_MAX");
	check(map->end + 1 <= map->max, "RadixMap is full");
	
	RMElement element = { .data = { .key = key, .value = value } };
	
	map->contents[map->end++] = element;
	
	RadixMap_sort(map);
	
	return 0;
error:
	return -1;
}

int RadixMap_delete(RadixMap* map, RMElement* el)
{
	check(map != NULL, "Invalid pointer to map");
	check(map->end > 0, "RadixMap is empty");
	check(el != NULL, "Invalid pointer to element");
	
	el->data.key = UINT32_MAX;
	if (map->end > 1) {
		RadixMap_sort(map);
	}
	
	map->end--;
	
	return 0;
error:
	return -1;
}
