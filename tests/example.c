#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>

#include "unit.h"


static void
test_xxx(void)
{
	header();

	/* some code */

	footer();
}

int
main(void)
{
	test_xxx();
}

