
#ifndef  __HTABLE_H_
#define  __HTABLE_H_

#define BUCKET_SIZE 65536
#define LINE_SIZE sizeof(ht_line)
#define HT_ELEMENTS 64


typedef struct  {
	uint16_t key;
	char data[2];
} ht_element;

typedef  struct  {
	ht_element elem[HT_ELEMENTS];
} ht_line;

typedef struct  {
	ht_line* line ;
} ht;



void ht_init( ht* ht);
void ht_free( ht* ht);

uint32_t ht_getlkey(uint32_t key);
uint32_t ht_getrkey(uint32_t key);

void ht_add(ht* ht, uint32_t key, char* value);

void ht_set(ht* ht, uint32_t key, char* value, int index);
ht_element* ht_get(ht* ht, uint32_t key, int index);



#endif /* __HTABLE_H_  */