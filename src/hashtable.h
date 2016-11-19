
#ifndef  __HTABLE_H_
#define  __HTABLE_H_

#define BUCKET_SIZE 	65536
#define LINE_SIZE 		sizeof(ht_line)
#define HT_ELEMENTS 	64
#define HT_OK 			0
#define HT_FAIL			1
#define HT_EXITS		2
#define HT_ERROR 		-1

#define TRUE			1
#define FALSE			0

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


/**
@brief инициализация хеш-таблицы, выделение памяти
@param ht*
Делается один раз в начале программы
*/
void ht_init( ht* ht);

/**
@brief деинициализация хеш-таблицы, освобождение памяти
@param ht*
Делается один раз в перед окончанием программы
*/
void ht_free( ht* ht);

/**
@brief добавление данных в хеш-таблицу
@param ht*
@param key
@param value
@return HT_RETUN_CODE
Добавляются данные в хеш-таблицу. 
Функция возвращает код:
 HT_OK 		вставка прошла успешно
 HT_EXITS	данные уже были вставлены ранее
 HT_ERROR 	ошибка переполнения
*/
int ht_add(ht* ht, uint32_t key, const char* value);


/**
@brief проверка наличия данных в хеш-таблице
@param ht*
@param key
@param value
@return HT_RETUN_CODE
Осуществляет проверку наличия данных в хештаблице.
Проверка осуществляется по ключу и первым двум байтам данных 
Функция возвращает код:
 HT_OK 		данные сущетвуют
 HT_FAIL	данные не существуют
*/
int ht_check(ht* ht, uint32_t key, const char* value);



#endif /* __HTABLE_H_  */