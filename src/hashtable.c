/*
	gcc -o ht -c  -O3  hashtable.c
*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "crc64.c"
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

inline uint8_t
ht_xor(const char* value, int len)
{
	char* p = (char*) value;
	uint8_t xres = 0;
	int i;
	for(i=0; i < len; i++){
		xres ^= *(p++);
	}

	return xres;
};


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
ht_add(ht* ht, const char* value)
{	
	
	size_t len = strlen(value) - 1;

	if (len <= 0)
		return HT_ERROR;

	ht_crc64 crc_s;
	crc_s.crc = crc64(0,(unsigned char*)value,(uint64_t)len);

	uint32_t rkey = ht_getrkey(crc_s.key);
	ht_line* pline ;
	HT_GETLINE(pline,crc_s.key);

	int i = 0;
	while ( i < HT_ELEMENTS){
		ht_element* el = &pline->elem[i];

		if (el->key == 0){
			// add here
			el->key = rkey;
			memcpy(el->hash, crc_s.hash, HT_VALUE_SIZE);

			return HT_OK;
		}

		if (el->key == rkey && ! memcmp(el->hash, crc_s.hash, HT_VALUE_SIZE)){
			return HT_EXIST;
		}
	
		i++;
	}

	return HT_ERROR;
}


int 
ht_check(ht* ht, const char* value)
{	
	size_t len = strlen(value) - 1;

	if (len <= 0)
		return HT_ERROR;

	ht_crc64 crc_s;
	crc_s.crc = crc64(0,(unsigned char*)value,(uint64_t)len);

	uint32_t rkey = ht_getrkey(crc_s.key);
	ht_line* pline ;
	HT_GETLINE(pline,crc_s.key);

	ht_element el = pline->elem[0];

	int i = 0;
	while ( i < HT_ELEMENTS){
		el = pline->elem[i];

		if (el.key == 0){
			return HT_FAIL;
		}
		
		if (el.key == rkey && ! memcmp(el.hash, crc_s.hash, HT_VALUE_SIZE)){
			return HT_OK;
		}
	
		i++;
	}

	return HT_FAIL;	
}
