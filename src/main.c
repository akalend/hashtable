/**
*  gcc -o test  -O3  main.c
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>

#include "crc32.c"
#include "hashtable.h"


int main(int argc, char** argv )
{
	FILE* fp = fopen("../test/test.file.txt", "r");
	char line[128];

	ht ht;
	ht_init(&ht);


	ht_free(&ht);


	return 0;

    if( fp == NULL ) {  
    	printf("file not found\n");                     
        return 1;
    }

	uint32_t crc_1 = 0xcd1944ce & 0xFFFF0000;

    int n = 100;
    while( fgets(line,128,fp)  ) {

    	size_t len = strlen(line);
		
		uint32_t crc = 0x0;
		
		crc = crc32(crc, (const void *) line, len);

		if ((crc & 0xFFFF0000) == crc_1) {
        	printf("%d\t%x\t%s",(int)len, crc, line);
    	}
    }

		


	return 0;
} 