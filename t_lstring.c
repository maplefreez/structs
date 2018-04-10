/*
 * Test suits for lstring.
 * Author : ez
 * Date : 2018/4/6
 */

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

static void t_str_cmp1 ();
static void t_str_cmp2 ();

static void t_str_concat ();

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

	t_str_cmp1 ();
	t_str_cmp2 ();
	t_str_concat ();
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

static void t_str_cmp1 () {
	int cmpres = 0x7F;
	/* 0x1 */
	plstring lopd = str_assume ("");
	plstring ropd = str_assume ("");

	assert (lopd != NULL && ropd != NULL);
	cmpres = str_cmp (lopd, ropd);
	assert (cmpres == 0);
	str_destroy (lopd);
	str_destroy (ropd);

	/* 0x2 */
	lopd = str_assume ("323");
	ropd = str_assume ("324");
	assert (lopd != NULL && ropd != NULL);
	cmpres = str_cmp (lopd, ropd);
	assert (cmpres == 1);
	str_destroy (lopd);
	str_destroy (ropd);

	/* 0x3 */
	lopd = str_assume ("3234");
	ropd = str_assume ("324");
	assert (lopd != NULL && ropd != NULL);
	cmpres = str_cmp (lopd, ropd);
	assert (cmpres == -1);
	str_destroy (lopd);
	str_destroy (ropd);

	/* 0x4 */
	lopd = str_assume ("");
	ropd = str_assume ("324");
	assert (lopd != NULL && ropd != NULL);
	cmpres = str_cmp (lopd, ropd);
	assert (cmpres == 3);
	str_destroy (lopd);
	str_destroy (ropd);

	/* 0x5 */
	lopd = str_assume ("343");
	ropd = str_assume ("");
	assert (lopd != NULL && ropd != NULL);
	cmpres = str_cmp (lopd, ropd);
	assert (cmpres == -3);
	str_destroy (lopd);
	str_destroy (ropd);

}

static void t_str_cmp2 () {
	int cmpres = 0x7F;
	/* 0x1 */
	plstring lopd = str_assume ("43789893");
	plstring ropd = str_assume ("43238,0843r3");

	assert (lopd != NULL && ropd != NULL);
	cmpres = str_cmp (lopd, ropd);
	/* length diffence */
	assert (cmpres == (12-8));
	str_destroy (lopd);
	str_destroy (ropd);

	/* 0x2 */
	lopd = str_assume ("43789893");
	ropd = str_assume ("43238,08");
	assert (lopd != NULL && ropd != NULL);
	cmpres = str_cmp (lopd, ropd);
	/* ASCII code diffence */
	assert (cmpres == ('2'-'7'));
	str_destroy (lopd);
	str_destroy (ropd);

	/* 0x3 */
	lopd = str_assume ("3437483194831");
	ropd = str_assume ("3437483194831");
	assert (lopd != NULL && ropd != NULL);
	cmpres = str_cmp (lopd, ropd);
	assert (cmpres == 0);
	str_destroy (lopd);
	str_destroy (ropd);
}

static void t_str_concat () {
	char* res2 = "arriveed", *p;
	int i = 0;
	plstring aopd = str_assume ("");
	plstring bopd = str_assume ("");
	plstring res = NULL;

	/* 0x1 */
	assert (aopd != NULL && bopd != NULL);
	res = str_concat (aopd, bopd);
	assert (res != NULL && res -> length == 0 &&
			res -> chunk == NULL);
	str_destroy (aopd);
	str_destroy (bopd);
	str_destroy (res);

	/* 0x2 */
	aopd = str_assume ("arrive");
	bopd = str_assume ("ed");
	assert (aopd != NULL && bopd != NULL);
	res = str_concat (aopd, bopd);
	assert (res != NULL && res -> length == 8 &&
			res -> chunk != NULL);
	for (p = res2, i = 0; *p; ++ p, ++ i)
		assert (res -> chunk [i] == *p);
	str_destroy (aopd);
	str_destroy (bopd);
	str_destroy (res);

}

