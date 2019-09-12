/* Date : 2019/9/9
 * Author : ez
 * Desc :  PAT B 1003
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int input_count;
static char input [106];

/* Main. */
int main (int argc, char* argv []) {
	int len; char* p;
	int left, center, right, 
			pidx, tidx, pcount, tcount, othercount;

	pidx = tidx = pcount = tcount = othercount = 0;
	if (scanf ("%d", &input_count)) ;

	while (input_count --) {
		left = center = right = 0,
		tcount = pcount = othercount = 0;
		/* Input. */
		if (scanf ("%s", input)) ;

		len = strlen (input);
		/* Judge. */
		p = input;
		while (*p) {
			if (*p == 'P') {
				pidx = p - input; pcount ++;
			} else if (*p == 'T') {
				tidx = p - input; tcount ++;
			} else if (*p != 'A')
				othercount ++;
			++ p;
		}

		/* Output. */
		if (othercount > 0 || pcount != 1 
				|| tcount != 1 || tidx - pidx <= 1) {
			puts ("NO"); continue;
		}

		left = pidx; center = tidx - pidx - 1; 
		right = len - tidx - 1;

		if (right - left * (center - 1) == left)
			puts ("YES");
		else
			puts ("NO");
	}

	return 0;
}

