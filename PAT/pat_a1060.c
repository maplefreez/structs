#include <stdio.h>

// static int get_pidx (char*);
static int get_offset (char*);
static void compare (char*, char*, int);
static void output (char*, int, int);

int main (int argc, char* argv []) {
	int n; char a [0x80], b [0x80];
	scanf ("%d %s %s", &n, a, b);
	compare (a, b, n);
	return 0;
}


static void compare (char* _a, char* _b, int _n) {
	int aoffset, boffset/*, apidx, bpidx */;
	int i = 0, cmp; char *pa, *pb;
	// apidx = get_pidx (_a);
	aoffset = get_offset (_a);
	boffset = get_offset (_b);
	// bpidx = get_pidx (_b);

	pa = _a + aoffset;
	pb = _b + boffset;

	while (i < _n) {
		cmp = pa [i] != pb [i];
		if (cmp) break;
		i ++;
	}

	if (cmp) {
		/* Not equal. */
		printf ("NO 0.");
		/* A */
		output (_a, aoffset, _n);
		printf ("*10^%d 0.", _n);

		/* B */
		output (_b, boffset, _n);
		printf ("*10^%d", _n);
	} else {
		/* Equal. */
		printf ("YES 0.");
		output (_a, aoffset, _n);
		printf ("*10^%d", _n);
	}
}


// static int get_pidx (char* _str) {
// 	char* p = _str;
// 	while (*p) {
// 		if (*p == '.') break;
// 		++ p;
// 	}
// 	return p - _str;
// }


static int get_offset (char* _str) {
	char* p = _str;
	while (*p) {
		if (*p != '0')
			break;
		++ p;
	}
	return p - _str;
}

static void output (char* _str, int _offset, int _n) {
		int i = 0;
		while (i < _n) {
			putchar (_str [_offset + i]);
			i ++;
		}
}

