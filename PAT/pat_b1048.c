/* Date : 2019/7/17
 * Author : ez
 * Desc :  PAT B 1048
 */

#include <stdio.h>
#include <string.h>

static char* __reverse (char* _s, int _n) {
	int i = 0;
	while (i < (_n >> 1)) {
		_s [i] ^= _s [_n - i - 1];
		_s [_n - i - 1] ^= _s [i];
		_s [i] ^= _s [_n - i - 1];
		i ++;
	}
	return _s;
}

char encode [0xD] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'J', 'Q',
	'K'
};

// #	define SUBMIT

#ifndef SUBMIT
/* 这部分是自己的代码. */
int main (int argc, char* argv []) {
	char salt [104] = {0, },
			 code [104] = {0, };
	int i, len, lens, lenc;

	if (scanf ("%s %s", salt + 1, code + 1)) ;
	lens = strlen (salt + 1);
	lenc = strlen (code + 1);
	len = lens < lenc ? lens : lenc;

	/* Reverse. */
	(void) __reverse (salt + 1, lens);
	(void) __reverse (code + 1, lenc);

	/* Encode */
	i ^= i;
	while (++ i <= len) {
		if (i & 0x01) code [i] = encode [
				(code [i] + salt [i] - 0x60) % 0xD
			];
		else {
			int tmp = code [i] - salt [i];
			code [i] = encode [tmp < 0 ? tmp + 10 : tmp];
		}
	}

	i = lenc;
	while (i ++ < lens)
		code [i] = i & 0x01 ?
			encode [salt [i] - 0x30] : 
			encode [0x3A - salt [i]];

	while (-- i >= 1) putchar (code [i]);

	return 0;
}
#endif

#ifdef SUBMIT
/* 这部分代码来自《算法笔记》, 使用了
 __reverse()函数.*/
int main (int argc, char* argv []) {
#	define 	maxn	110
	char A [maxn], B [maxn], ans [maxn] = {0, };
	scanf ("%s %s", A, B);
	int lenA = strlen (A);
	int lenB = strlen (B);
	int len = lenA > lenB ? lenA : lenB;

	__reverse (A, lenA);
	__reverse (B, lenB);
	for (int i = 0; i < len; ++ i) {
		int numA = i < lenA ? A [i] - '0' : 0;
		int numB = i < lenB ? B [i] - '0' : 0;
		if (i % 2 == 0) {
			int temp = (numA + numB) % 0x0D;
			if (temp == 10) ans [i] = 'J';
			else if (temp == 11) ans [i] = 'Q';
			else if (temp == 12) ans [i] = 'K';
			else ans [i] = temp + '0';
		} else {
			int temp = numB - numA;
			if (temp < 0) temp += 10;
			ans [i] = temp + '0';
		}
	}

	__reverse (ans, len);
	puts (ans);
	return 0;

	return 0;
}
#endif
