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
