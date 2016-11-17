/*
	gcc -o ht -c  -O3  hashtable.c
*/

#include <stdint.h>
#include <stdlib.h>
#include "hashtable.h"

#define BUCKET_SIZE 65536

void ht_init(ht* ht)
{
	ht->line = (ht_line*) malloc( sizeof(ht_line) * BUCKET_SIZE);

	printf("allocated %d\n", sizeof(ht_line) * BUCKET_SIZE);
}

void ht_free(ht* ht)
{
	free(ht->line);
}


uint32_t ht_getlkey(uint32_t key)
{
	return key >> 16;
}

uint32_t ht_getrkey(uint32_t key)
{
	return key & 0x0000FFFF;
}
