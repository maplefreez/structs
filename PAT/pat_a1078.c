/* Date : 2019/12/30
 * Author : ez
 * Desc :  PAT A 1078
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int hash_size;
int hash_table [10004];

static int _is_prime (int);
static int _adjust_size (int);
static int _hash (int);

/* TODO... Shell be submitted.*/
int main (int argc, char* argv []) {
	int count, i = 0;
	if (scanf ("%d %d", &hash_size, &count));

	hash_size = _adjust_size (hash_size);
	while (i ++ < count) {
		int num, idx;
		if (scanf ("%d", &num));

		/* Calculate index in the hash table. */
		idx = _hash (num);
		if (idx < 0) putchar ('-');
		else printf ("%d", idx);

		if (i < count) putchar (' ');
	}
	return 0;
}

static int _is_prime (int x) {
	int i = 2, right = (int) sqrt (x);
	for (; i <= right; ++ i)
		if (x % i == 0) return 0;
	return 1;
}

/* Adjust _original number to a 
 prime number larger than itself. */
static int _adjust_size (int _original) {
	int loop = _original << 1;
	if (_is_prime (_original)) 
		return _original;

	_original += _original & 0x01 ? 2 : 1;
	while (_original < loop) {
		if (_is_prime (_original)) break;
		_original += 2;
	}
	return _original;
}

static int _hash (int _key) {
	int idx = _key % hash_size, i = 0;
	/* Insert. */
	if (! hash_table [idx]) { 
		hash_table [idx] = 1; 
		return idx; 
	} else
		// Collision happens.
		while (i < hash_size) {
			idx = (_key + i * i) % hash_size;
			/* Insert. */
			if (! hash_table [idx]) {
				hash_table [idx] = 1; 
				return idx;
			}

			++ i;
		}
	return -1;
}


