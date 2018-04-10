#include "lstring.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/****** Pre-defination for test suits. ******/
static void t_str_assert1 ();
static void t_str_assert2 ();
static void t_str_destroy ();

static void t_str_length1 ();
static void t_str_length2 ();

static void t_str_clear1 ();

static void t_str_substring1 ();
static void t_str_substring2 ();

/* Main test entry. */
int main (int argc, char* argv []) {
	t_str_destroy ();
	t_str_assert1 ();
	t_str_assert2 ();

	t_str_length1 ();
	t_str_length2 ();

	t_str_clear1 ();
	t_str_substring1 ();
	t_str_substring2 ();
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
	assert (*p == 'O' && *(p + 1) == 'K' 
			&& *(p + 2) == '\0');
	str_destroy (p1);
}


static void t_str_length1 () {
	plstring p1 = NULL;
	int ret_length = str_length (p1);

	assert (ret_length == -1);
}


static void t_str_length2 () {
	char* ptr = "123456789ABCDE";
	plstring p1 = str_assume (ptr);

	assert (p1 -> length == 14);
}


static void t_str_destroy () {
	str_destroy (NULL);
}


static void t_str_clear1 () {
	plstring p = str_assume (NULL);
	int ret_code = str_clear (p); // Doing nothing.
	assert (ret_code == STAT_ERR);

	p = str_assume ("abcd");
	ret_code = str_clear (p);

	assert (ret_code == STAT_SUCC);
	assert (p != NULL);
	assert (p -> length == 0);
	assert (p -> chunk == NULL);
}


static void t_str_substring1 () {
	char* pch = NULL;
	plstring p = str_assume ("123abcd456");
	assert (p != NULL);

	/* Should be 'abc' */
	plstring res1 = str_substring (p, 3, 3);
	assert (res1 != NULL && res1 -> length == 3);

	pch = res1 -> chunk;
	assert (*pch == 'a' && *(pch + 1) == 'b'
			&& *(pch + 2) == 'c' && *(pch + 3) == '\0');
	str_destroy (res1);
	str_destroy (p);
}

static void t_str_substring2 () {
	char* res1 = "49999"; int i;
	plstring p = NULL;
	plstring res = str_substring (p, 3, 9);
	assert (res == NULL);

	p = str_assume ("12349999");
	/* Should be '49999' */
	res = str_substring (p, 3, 8);
	assert (res != NULL && res -> length == 5);
	for (i = 0; i < strlen (res1); ++ i)
		assert ((res -> chunk) [i] == res1 [i]);
	assert (res -> chunk [i] == '\0');
	str_destroy (res);

	/* Should be '123' */
	res = str_substring (p, 0, 3);
	assert (res != NULL && res -> length == 3);
	assert (res -> chunk [0] == '1' && 
			res -> chunk [1] == '2' &&
			res -> chunk [2] == '3');
	assert (res -> chunk [3] == '\0');
	str_destroy (res);

	/* Should be NULL */
	res = str_substring (p, 0, 0);
	assert (res == NULL);
	res = str_substring (p, -1, 0);
	assert (res == NULL);
	res = str_substring (p, 1, 0);
	assert (res == NULL);
	res = str_substring (p, 8, 0);
	assert (res == NULL);
	res = str_substring (p, 8, 5);
	assert (res == NULL);
	res = str_substring (p, 8, 1024);
	assert (res == NULL);
}


