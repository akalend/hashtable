/*
	gcc -o ht -c  -O3  hashtable.c
*/

#include <stdint.h>
#include <stdlib.h>
#include "hashtable.h"


void ht_init(ht* ht)
{
	ht->line = (ht_line*) malloc( sizeof(ht_line) * BUCKET_SIZE);
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


void ht_add(ht* ht, uint32_t key, char* value)
{

}

ht_element*  ht_get(ht* ht, uint32_t key, int index)
{

	if (index >= HT_ELEMENTS)
		exit(7);

	uint32_t lkey = ht_getlkey(key);

	ht_line* pline ;

	pline = ht->line;
	pline += lkey;

	return &pline->elem[index];
}

void ht_set(ht* ht, uint32_t key, char* value, int index)
{

	if (index >= HT_ELEMENTS)
		exit(7);

	ht_line* pline = ht->line;
	pline += ht_getlkey(key);

	ht_element *el = pline->elem + index;
	el->key = ht_getrkey(key);
}

