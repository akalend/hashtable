#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "unit.h"
#include "../src/hashtable.h"


static void
test_check(void)
{
	header();

	uint32_t key = 0xcd198be0;
	char value[2] = {'a','b'};

	ht ht;
	ht_init(&ht);

	ht_add(&ht,  value);

	value[0] = 'c';
	value[1] = 'd';
	ht_add(&ht,  value);

	value[0] = 'x';
	value[1] = 'z';
	ht_add(&ht,  value);

	value[0] = 'a';
	value[1] = 'b';

	int res = ht_check(&ht, key, value);
	is( res, HT_OK, "ab find [%d]", res);	


	value[0] = 'a';
	value[1] = 'c';

	int res2 = ht_check(&ht, key, value);
	is( res2 , 1, "ac find [%d, %.2s]", res, value);	

	value[0] = 'c';
	value[1] = 'd';

	res = ht_check(&ht, key, value);
	is( res, HT_OK, "cd find [%d]", res);	


	value[0] = 'x';
	value[1] = 'z';

	res = ht_check(&ht, key, value);
	is( res, HT_OK, "cd find [%d]", res);	


	value[0] = 'c';
	value[1] = 'd';

	key++;
	int res3 = ht_check(&ht, key, value);
	is( res3, HT_FAIL, "## new key: cd find [%d]", res3);


	ht_free(&ht);

	footer();
}



static void
test_not_add(void)
{
	header();

	uint32_t key = 0xcd198be0;
	char value[2] = {'z','z'};

	ht ht;
	ht_init(&ht);

	int res = ht_check(&ht, key, value);
	printf("*** ht_result %d  %d\n", res,  res == HT_FAIL );
	is( res, 1, "zz not find [%d %.2s]", res, value);

	ht_add(&ht, value);

	int res2 = ht_check(&ht, key, value);
	is( res2, 0, "zz find [%d %.2s]", res2, value);	


	ht_free(&ht);

	footer();
}

static void
test_duble_add(void)
{
	header();

	uint32_t key = 0xad198be0;
	char value[2] = {'z','z'};

	ht ht;
	ht_init(&ht);

	int res = ht_check(&ht, key, value);
	is( res, 1, "zz not find [%d %.2s]", res, value);

	res = ht_add(&ht, value);

	int res2 = ht_check(&ht, key, value);
	is( res2, 0, "zz find [%d %.2s]", res2, value);	

	int res5 = ht_add(&ht, value);

	int res3 = ht_check(&ht, key, value);
	is( res3, 0, "zz find [%d %.2s]", res3, value);	

	ht_free(&ht);

	footer();
}


static void
test_xor(void)
{
	header();

	char value2[2] = { 0x04, 0x10 };


	uint32_t res = ht_xor(value2,2);

	printf("res2 %X\n", res);

	is( 0x0014, res,  "0x04 XOR 0x10 = %x" , res);


	char value3[2] = { 0x44, 0x40 };


	res = ht_xor(value3,2);

	printf("res3 %X\n", res);

	is( res, 0x4, "0x44 XOR 0x40 = %x", res );

	char value[2] = { 0x04, 0x04 };

	uint32_t res2 = ht_xor(value,2);

	printf("res %X\n", res);

	is( res2, 0, "0x04 XOR 0x04 = 0" );

	footer();
}


int
main(void)
{
	// plan(10);

	// test_not_add();
	// test_check();
	// test_duble_add();

	test_xor();

	// check_plan();

	return EXIT_SUCCESS;
}

