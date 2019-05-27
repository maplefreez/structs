/* Date : 2018/12/25
 * Author : ez
 * Desc : PAT B 1036
 */

#include <stdio.h>
void depict (int _l, char _ch) {
	int center = (_l & 0x01) + (_l >> 1) - 2, i, j;
	/* first line. */
	for (i = 0; i < _l; ++ i)
		putchar (_ch);
	puts ("");

	if (center > 0) {
		for (i = 0; i < center; ++ i) {
			/* Each line. */
			putchar (_ch);
			for (j = 0; j < _l - 2; ++ j) 
				putchar (' ');
			putchar (_ch);
			puts ("");
		}
	}
	
	/* last line. */
	for (i = 0; i < _l; ++ i)
		putchar (_ch);
}

/*
int main (int argc, char* argv []) {
	int i = 20;
	while (i >= 3) {
		depict (i --, 'a');
		puts ("");
	}
	return 0;
}
*/

// Submit code
int main (int argc, char* argv []) {
	int _l, i, j, center; char _ch;

	scanf ("%d %c", &_l, &_ch);
	center = (_l & 0x01) + (_l >> 1) - 2;

	/* first line. */
	for (i = 0; i < _l; ++ i)
		putchar (_ch);
	puts ("");

	if (center > 0) {
		for (i = 0; i < center; ++ i) {
			/* Each line. */
			putchar (_ch);
			for (j = 0; j < _l - 2; ++ j) 
				putchar (' ');
			putchar (_ch);
			puts ("");
		}
	}
	
	/* last line. */
	for (i = 0; i < _l; ++ i)
		putchar (_ch);
	return 0;
}
