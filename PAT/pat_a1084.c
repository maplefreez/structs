/* Date : 2019/9/7
 * Author : ez
 * Desc :  PAT A 1084
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static bool has_output [128] = {false, };
static char right_string [96], err_string [96];

#	define __to_capa(__C, __v)     \
	do {											\
		if (__C >= 'a' && __C <= 'z') __v = __C - 32;	\
		else __v = __C;  \
	} while (0)

int main (int  argc, char* argv []) {
	int i = 0, j = 0; size_t right_len, err_len;
	if (scanf ("%s\n%s", right_string, err_string));

	right_len = strlen (right_string);
	err_len = strlen (err_string);

	while (i < right_len) {
		char r, e;
		__to_capa (right_string [i], r); j = 0;
		while (j < err_len) {
			__to_capa (err_string [j], e);
			if (e == r) break;
			else j ++;
		}
		if (j == err_len && ! has_output [(int) r]) {
			putchar (r); has_output [(int) r] = true;
		}
		i ++;
	}

	return 0;
}

