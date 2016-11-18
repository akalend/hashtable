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
test_add(void)
{
	header();

	uint32_t key = 0xcd198be0;
	char value[2] = {'a','b'};

	ht ht;
	ht_init(&ht);

	ht_add(&ht, key, value);
	is(1, 1, "test add");

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

	ht_free(&ht);

	footer();
}

int
main(void)
{
	// test_getlkey();
	// test_getrkey();
	// test_set();
	// test_add();
	test_find();
}

