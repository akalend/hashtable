
#ifndef  __HTABLE_H_
#define  __HTABLE_H_

#define BUCKET_SIZE 	65536
#define LINE_SIZE 		sizeof(ht_line)
#define HT_ELEMENTS 	64
#define HT_OK 			0
#define HT_FAIL			1
#define HT_EXITS		2
#define HT_ERROR 		-1



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


#define HT_GETLINE(pline) 			\
	uint32_t lkey = ht_getlkey(key);\
	pline = ht->line;				\
	pline += lkey;


void ht_init( ht* ht);
void ht_free( ht* ht);

int ht_add(ht* ht, uint32_t key, const char* value);
int ht_check(ht* ht, uint32_t key, const char* value);



#endif /* __HTABLE_H_  */