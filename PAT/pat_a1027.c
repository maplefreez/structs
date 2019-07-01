/*
 * Author : ez
 * Date : 2019/6/30
 * Desc : PAT A 1058
 */

#include <stdio.h>

const char digit [14] = {
	'0', '1', '2', '3', '4',
	'5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D'
};

int main (int argc, char* argv []) {
	unsigned int r, g, b;
	char output [8] = {0, };

	(void) scanf ("%d %d %d", &r, &g, &b);
	output [0] = '#';
	/* R */
	output [1] = digit [r / 13];
	output [2] = digit [r % 13];

	/* G */
	output [3] = digit [g / 13];
	output [4] = digit [g % 13];

	/* B */
	output [5] = digit [b / 13];
	output [6] = digit [b % 13];

	output [7] = '\0';

	puts (output);
	return 0;
}
