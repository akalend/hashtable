#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "unit.h"
#include "../src/hashtable.h"



static void
test_set(void)
{
	header();

	uint32_t key = 0xcd198be0;
	char value[2] = {'a','b'};

	ht ht;
	ht_init(&ht);

	ht_set(&ht, key, (char*)value, 63);
	ht_element* get_key = ht_get(&ht, key, 63);

	is(0x8be0, get_key->key, "0x8be0 == key");
	is( strcmp("ab", get_key->data) , 0, "ab == data");

	ht_free(&ht);

	footer();
}


static void
test_find(void)
{
	header();

	uint32_t key = 0xcd198be0;
	char value[2] = {'a','b'};

	ht ht;
	ht_init(&ht);

	int i = ht_find_notnull(&ht, key);

	is(i, 0, "key null");


	ht_set(&ht, key, (char*)value, 0);
	i = ht_find_notnull(&ht, key);
	is(i, 1, "key=%d [1]", i);


	ht_set(&ht, key, (char*)value, 1);
	i = ht_find_notnull(&ht, key);
	is(i, 2, "key=%d [2]",i);


	ht_set(&ht, key, (char*)value, 2);
	i = ht_find_notnull(&ht, key);
	is(i, 3, "key=%d [3]",i);

	ht_set(&ht, key, (char*)value, 3);
	i = ht_find_notnull(&ht, key);
	is(i, 4, "key=%d [4]",i);

	ht_free(&ht);

	footer();
}


static void
test_add(void)
{
	header();

	uint32_t key = 0xcd198be0;
	char value[2] = {'a','b'};

	ht ht;
	ht_init(&ht);

	ht_add(&ht, key, value);

	value[0] = 'c';
	value[1] = 'd';
	ht_add(&ht, key, value);

	ht_element* get_key = ht_get(&ht, key, 0);
	is(strncmp("ab", get_key->data, 2) , 0, "ab == data");

	get_key = ht_get(&ht, key, 1);
	is(strncmp("cd", get_key->data, 2) , 0, "cd == data");


	value[0] = 'x';
	value[1] = 'z';
	ht_add(&ht, key, value);

	get_key = ht_get(&ht, key, 2);
	is(strncmp("xz", get_key->data, 2) , 0, "xz == data");

	ht_free(&ht);

	footer();
}

static void
test_check(void)
{
	header();

	uint32_t key = 0xcd198be0;
	char value[2] = {'a','b'};

	ht ht;
	ht_init(&ht);

	ht_add(&ht, key, value);

	value[0] = 'c';
	value[1] = 'd';
	ht_add(&ht, key, value);

	value[0] = 'x';
	value[1] = 'z';
	ht_add(&ht, key, value);

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
	res = ht_check(&ht, key, value);
	is( res, HT_FAIL, "## new key: cd find [%d]", res);	


	ht_free(&ht);

	footer();
}


int
main(void)
{
	test_set();	
	test_find();
	test_add();
	test_check();
}

