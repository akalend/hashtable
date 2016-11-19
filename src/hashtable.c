/*
	gcc -o ht -c  -O3  hashtable.c
*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"


inline uint32_t
ht_getlkey(uint32_t key)
{
	return key >> 16;
}


inline uint32_t
ht_getrkey(uint32_t key)
{
	return key & 0x0000FFFF;
}


void
ht_init(ht* ht)
{
	ht->line = (ht_line*) calloc( sizeof(ht_line),  BUCKET_SIZE);
}


void
ht_free(ht* ht)
{
	free(ht->line);
}


int
ht_find_notnull(ht* ht, uint32_t key)
{
	ht_line* pline ;
	HT_GETLINE(pline);

	ht_element el = pline->elem[0];

	if (el.key == 0)
		return 0;

	int i = 0;
	while ( i < HT_ELEMENTS){
		el = pline->elem[i];
		if (el.key == 0) 
			return i;		
		i++;
	}

	return HT_ERROR;
}

ht_element*
ht_get(ht* ht, uint32_t key, int index)
{
	if (index >= HT_ELEMENTS)
		exit(7);

	ht_line* pline ;
	HT_GETLINE(pline);

	return &pline->elem[index];
}


int
ht_set(ht* ht, uint32_t key, const char* value, int index)
{
	if (index >= HT_ELEMENTS)
		return HT_ERROR;

	ht_line* pline = ht->line;
	pline += ht_getlkey(key);

	ht_element *el = pline->elem + index;
	el->key = ht_getrkey(key);
	memcpy((void*)el->data, value, 2);

	return HT_OK;
}


int
ht_add(ht* ht, uint32_t key, const char* value)
{	
	
	uint32_t rkey = ht_getrkey(key);
	ht_line* pline ;
	HT_GETLINE(pline);

	int i = 0;
	while ( i < HT_ELEMENTS){
		ht_element* el = &pline->elem[i];

		if (el->key == 0){
			// add here
			el->key = rkey;
			memcpy(el->data, value, 2);

			return HT_OK;
		}

		if (el->key == rkey && !memcmp(el->data, value, 2)){
			return HT_EXITS;
		}
	
		i++;
	}

	return HT_ERROR;
}


int ht_check(ht* ht, uint32_t key, const char* value)
{	
	uint32_t rkey = ht_getrkey(key);
	ht_line* pline ;
	HT_GETLINE(pline);

	ht_element el = pline->elem[0];

	int i = 0;
	while ( i < HT_ELEMENTS){
		el = pline->elem[i];

		if (el.key == 0){
			return HT_FAIL;
		}

		if (el.key == rkey && !memcmp(el.data, value, 2)){
			return HT_OK;
		}
	
		i++;
	}

	return HT_FAIL;	
}
