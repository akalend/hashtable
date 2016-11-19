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

	int res;
    while( fgets(line,128,fp) ) {

    	size_t len = strlen(line);
		
		uint32_t crc = 0x0;
		crc = crc32(crc, (const void *) line, len);

		res = ht_add(&ht, crc, line);
		int is_exist = FALSE;	
		if (res == HT_EXITS) {
			is_exist = TRUE;			
		} 

		printf("%s\n", is_exist ? "YES" : "NO" );
    }

	ht_free(&ht);
	fclose(fp);

	return 0;
} 