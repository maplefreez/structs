/* Date : 2019/12/30
 * Author : ez
 * Desc :  PAT A 1015
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int _digits [0x20];
static int _dig_count;

static int _is_prime (int);
static int _reverse (int, int);

int main (int argc, char* argv []) {
	int num, radix;
	while (1) {
		if (scanf ("%d", &num));
		if (num < 0) break;

		if (scanf ("%d", &radix));
		if (! _is_prime (num)) {
			puts ("No");
			continue;
		}

		_dig_count = 0;
		num = _reverse (num, radix);
		if (_is_prime (num)) puts ("Yes");
		else puts ("No");
	}
	return 0;
}

static int _is_prime (int x) {
	int i = 2, right = (int) sqrt (x);

	if (x <= 1) return 0;
	for (; i <= right; ++ i)
		if (x % i == 0) return 0;
	return 1;
}

static int _reverse (int _x, int _radix) {
	int reverse = 0, i = 0;
	do {
		_digits [_dig_count ++] = _x % _radix;
		_x /= _radix;
	} while (_x);

	i = 0;
	while (i < _dig_count) {
		reverse *= _radix;
		reverse += _digits [i ++];
	}

	return reverse;
}


