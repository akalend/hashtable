/**
*  gcc -o test  -O3  main.c
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "crc32.c"
#include "hashtable.h"


int main(int argc, char** argv )
{
	FILE* fp = fopen("../tools/test.file.txt", "r");
	char line[128];

	ht ht;
	ht_init(&ht);


    if( fp == NULL ) {  
    	printf("file not found\n");                     
        return 1;
    }

	uint32_t crc_1 = 0xcd1944ce & 0xFFFF0000;

    int n = 100;
    while( fgets(line,128,fp) && n--  ) {

    	size_t len = strlen(line);
		
		uint32_t crc = 0x0;
		
		crc = crc32(crc, (const void *) line, len);

		ht_add(&ht, crc, line);
		int res = ht_check(&ht, crc, line);
		if (res == HT_OK) {
			printf("%x:\t%d\t%10s\n", crc, res, line);
		}
    }

		

	ht_free(&ht);

	return 0;
} 