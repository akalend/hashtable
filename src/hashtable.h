
#ifndef  __HTABLE_H_
#define  __HTABLE_H_

typedef struct  {
	uint16_t key;
	char data[2];
} ht_element;

typedef  struct  {
	ht_element elem[64];
} ht_line;

typedef struct  {
	ht_line* line ;
} ht;



void ht_init( ht* ht);
void ht_free( ht* ht);


#endif /* __HTABLE_H_  */