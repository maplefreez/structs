#include "lstring.h"
#include <stdlib.h>
#include <assert.h>

/****** Pre-defination for test suits. ******/
static void t_str_assert1 ();
static void t_str_assert2 ();

/* Main test entry. */
int main (int argc, char* argv []) {
	t_str_assert1 ();
	t_str_assert2 ();
	return 0;
}


/******* Implementation for each test suit. ******/
static void t_str_assert1 () {
	plstring p1 = str_assume ("");
	assert (p1 != NULL);
	assert (p1 -> length == 0);
	assert (p1 -> chunk == NULL);

	str_destroy (p1);

	/* The same as NULL. */
	p1 = str_assume ('\0');
	assert (p1 == NULL);
}

static void t_str_assert2 () {
	char* p = NULL;
	plstring p1 = str_assume (NULL);
	assert (p1 == NULL);

	p1 = str_assume ("OK");
	assert (p1 != NULL);
	assert (p1 -> length == 2);

	p = p1 -> chunk;
	assert (*p == 'O' && *(p + 1) == 'K');
	str_destroy (p1);
}

