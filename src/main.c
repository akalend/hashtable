/**
*  gcc -o test  -O3  main.c
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "hashtable.h"

#define LINE_SIZE 	128

int main(int argc, char** argv )
{
	

	if (argc == 1 || argc > 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return EXIT_SUCCESS;
	}


	FILE* fp = fopen( argv[1], "r");


	if (fp == NULL) {

		printf("Cannot open file: %s\n", strerror(errno));
		return EXIT_SUCCESS;
	}

	char line[LINE_SIZE];

	ht ht;
	ht_init(&ht);

    if( fp == NULL ) {  
    	printf("file not found\n");                     
        return 1;
    }

    while( fgets(line,LINE_SIZE,fp) ) {

		int res = ht_add(&ht, line);
		if (res == HT_EXIST)
			printf("len=%d\t%s",(int)strlen(line), line);
    }

	fclose(fp);

    while( fgets(line,LINE_SIZE,stdin) ) {
		

		int res = ht_check(&ht, line);

		if ( strncmp(line,"exit", 4) == HT_OK ) {
			ht_free(&ht);
			return EXIT_SUCCESS;
		}
		printf("len=%d[%d] %s\n", res,(int)strlen(line), line);
		printf("%s\n", (res == HT_OK ? "YES" : "NO") );

	}


	ht_free(&ht);
	return EXIT_SUCCESS;
} 