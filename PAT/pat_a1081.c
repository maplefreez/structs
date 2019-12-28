/* Date : 2019/12/26
 * Author : ez
 * Desc :  PAT A 1081
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct fraction {
	long long up;
	long long down;
} fraction, *pfraction;

static long long GCD (long long _a, long long _b) {
	if (_b == 0) return _a;
	return GCD (_b, _a % _b);
}

/* Add _b to _a. */
static pfraction _add (pfraction _a, pfraction _b) {
	_a -> up = _a -> up * _b -> down + 
		_b -> up * _a -> down;
	_a -> down = _a -> down * _b -> down;
	return _a;
}

static void _reduction (pfraction _a) {
	long long gcd = GCD (llabs (_a -> up), 
			llabs (_a -> down));
	_a -> up /= gcd;
	_a -> down /= gcd;
	return;
}

static void _display (pfraction _a) {
	if (_a -> up == 0 || 
			(_a -> up != 0 && ! (_a -> up % _a -> down)))
		printf ("%lld", _a -> up / _a -> down);
	else {
		if (_a -> up / _a -> down)
			printf ("%lld %lld/%lld", 
					_a -> up / _a -> down,
					_a -> up % _a -> down, 
					_a -> down);
		else
			printf ("%lld/%lld", _a -> up, _a -> down);
	}
}

/* TODO... Shell be submit. */
int main (int argc, char* argv []) {
	int n = 0, i = 1;
	fraction a, sum;
	if (scanf ("%d", &n));
	if (n <= 0) {
		puts ("0");
		return 0;
	}

	if (scanf ("%lld/%lld", &sum.up, &sum.down));

	while (i ++ < n) {
		/* A */
		if (scanf ("%lld/%lld", &a.up, &a.down));
		_add (&sum, &a);
		_reduction (&sum);
	}

	_display (&sum);
	return 0;
}

