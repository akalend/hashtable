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
    int n = 20;
    while( fgets(line,128,fp) && n--  ) {

    	size_t len = strlen(line);
		
		uint32_t crc = 0x0;
		
		crc = crc32(crc, (const void *) line, len);

		if (0x61e4e146 == crc) {
			printf("%x:***\t%10s", crc, line);
		}

		res = ht_add(&ht, crc, line);
		printf("%d\t#%d. ", n, res);

		res = ht_check(&ht, crc, line);
		// if (res == HT_OK) {
			printf("%x:\t%d\t%10s", crc, res, line);
		// }
    }

		

	ht_free(&ht);
	fclose(fp);

	return 0;
} 