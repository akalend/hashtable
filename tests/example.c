#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>

#include "unit.h"
#include "../src/hashtable.h"



static void
test_getlkey(void)
{
	header();

	uint32_t crc = 0xcd198be0;

	uint32_t key = ht_getlkey(crc);	
	is(0xcd19, key, "0xcd19 == key");


	footer();
}

static void
test_getrkey(void)
{
	header();

	uint32_t crc = 0xcd198be0;
	uint32_t key = ht_getrkey(crc);
	
	is(0x8be0, key, "0x8be0 == key");

	footer();
}


int
main(void)
{
	test_getlkey();
	test_getrkey();
}

