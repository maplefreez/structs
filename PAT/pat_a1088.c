/* Date : 2019/12/26
 * Author : ez
 * Desc :  PAT A 1081
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct fraction {
	long long up;
	long long down;
} fraction, *pfraction;

/* Calculate and output. */
static void _add (pfraction, pfraction, pfraction);
static void _sub (pfraction, pfraction, pfraction);
static void _mul (pfraction, pfraction, pfraction);
static void _div (pfraction, pfraction, pfraction);

static long long GCD (long long, long long);
static pfraction _reduction (pfraction);
static void _disp (pfraction);


/* TODO... Shell be submitted. */
int main (int argc, char* argv []) {
	fraction a, b, res;
	res.up = res.down = 0ll;

	if (scanf ("%lld/%lld %lld/%lld",
				&a.up, &a.down, &b.up, &b.down));

	_add (&a, &b, &res);
	_sub (&a, &b, &res);
 	_mul (&a, &b, &res);
 	_div (&a, &b, &res);
	return 0;
}


static long long GCD (long long _a, long long _b) {
	if (_b == 0) return _a;
	return GCD (_b, _a % _b);
}

static void _add (pfraction _a, pfraction _b, pfraction _res) {
	_res -> up = _a -> up * _b -> down + 
		_b -> up * _a -> down;
	_res -> down = _a -> down * _b -> down;
	/* A */
	_reduction (_a);
	_disp (_a);
	/* + */
	putchar ('+');
	/* B */
	_reduction (_b);
	_disp (_b);
	/* = */
	putchar ('=');
	/* RES */
	_reduction (_res);
	_disp (_res);

	puts ("");
}

static void _sub (pfraction _a, pfraction _b, pfraction _res) {
	_res -> up = _a -> up * _b -> down - 
		_b -> up * _a -> down;
	_res -> down = _a -> down * _b -> down;
	/* A */
	_reduction (_a);
	_disp (_a);
	/* + */
	putchar ('-');
	/* B */
	_reduction (_b);
	_disp (_b);
	/* = */
	putchar ('=');
	/* RES */
	_reduction (_res);
	_disp (_res);

	puts ("");
}

static void _mul (pfraction _a, pfraction _b, pfraction _res) {
	_res -> up = _a -> up * _b -> up;
	_res -> down = _a -> down * _b -> down;
	/* A */
	_reduction (_a);
	_disp (_a);
	/* + */
	putchar ('*');
	/* B */
	_reduction (_b);
	_disp (_b);
	/* = */
	putchar ('=');
	/* RES */
	_reduction (_res);
	_disp (_res);

	puts ("");
}

static void _div (pfraction _a, pfraction _b, pfraction _res) {
	/* A */
	_reduction (_a);
	_disp (_a);
	/* + */
	putchar ('/');
	/* B */
	_reduction (_b);
	_disp (_b);
	/* = */
	putchar ('=');

	/* A / 0 = Inf */
	if (_b -> up == 0) {
		printf ("%s", "Inf");
	} else {
		_res -> up = _a -> up * _b -> down;
		_res -> down = _a -> down * _b -> up;
		if (_res -> up < 0 || _res -> down < 0) {
			_res -> up = - llabs (_res -> up);
			_res -> down = llabs (_res -> down);
		}
		/* RES */
		_reduction (_res);
		_disp (_res);
	}

	puts ("");
}

static pfraction _reduction (pfraction _a) {
	long long gcd = GCD (llabs (_a -> up), 
			llabs (_a -> down));
	_a -> up /= gcd;
	_a -> down /= gcd;
	return _a;
}

static void _disp (pfraction _a) {
	long long div = (_a -> up) / (_a -> down);
	long long mod = llabs (_a -> up) % (_a -> down);

	if (_a -> up == 0) {
		putchar ('0');
		return;
	}

	if (_a -> up < 0)
		printf ("%s", "(");

	if (div == 0)
		// when up = 0
		printf ("%lld/%lld", _a -> up, _a -> down);
	else {
		if (mod)
			// when ! (down | up)
			printf ("%lld %lld/%lld", div, mod, _a -> down);
		else
			// when (down | up).
			printf ("%lld", div);
	}

	if (_a -> up < 0)
		putchar (')');
}


