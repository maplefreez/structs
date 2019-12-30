/* Date : 2019/12/30
 * Author : ez
 * Desc :  PAT B 1013
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int _prime_count = 0;
static int _prime [10004];
static int _is_prime (int);
static int _create_prime (int);

/* Second. Shell be submitted. */
int main (int argc, char* argv []) {
	int m, n, i; int row = 0;
	if (scanf ("%d %d", &m, &n));
	_create_prime (n);
	i = m - 1;
	while (i < n) {
		if (row <= 8) 
			row ++, printf ("%d ", _prime [i ++]);
		else
			row ^= row, printf ("%d\n", _prime [i ++]); 
	}
	return 0;
}


/* First. */
// int main (int arg, char* argv []) {
// 	int min, max; int i, row = 0;
// 	if (scanf ("%d %d", &min, &max));
// 
// 	for (i = min; i <= max; i += 2) {
// 		if (_is_prime (i)) {
// 			if (row <= 8) row ++, printf ("%d ", i);
// 			else
// 				row ^= row, printf ("%d\n", i); 
// 		}
// 	}
// 
// 	return 0;
// }

static int _create_prime (int xth) {
	int i = 3; 
	// _prime [_prime_count ++] = 1;
	_prime [_prime_count ++] = 2;
	while (_prime_count < xth) {
		if (_is_prime (i))
			_prime [_prime_count ++] = i;
		i += 2;
	}
	return _prime_count;
}

static int _is_prime (int x) {
	int i = 2, right = (int) sqrt (x);
	for (; i <= right; ++ i)
		if (x % i == 0) return 0;
	return 1;
}

