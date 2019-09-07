/* Date : 2019/9/7
 * Author : ez
 * Desc :  PAT B 1042
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int hash_table [32] = {0, };

int main (int argc, char* argv []) {
	int max = 31; char ch; int i = 0;

	/* Input. */
	while (scanf ("%c", &ch) != EOF) {
		if (ch == '\n') break;
		if (! isalpha (ch)) continue;
		ch = tolower (ch);
		hash_table [(int) ch - 'a'] ++;
	}

	/* Output. */
	while (i < 26) {
		if (hash_table [max] < hash_table [i])
			max = i;
		++ i;
	}

	printf ("%c %d", max + 'a', hash_table [max]);
	return 0;
}

