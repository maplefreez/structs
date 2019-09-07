/* Date : 2019/9/7
 * Author : ez
 * Desc :  PAT A 1041
 */

#include <stdio.h>
#include <string.h>

static int input_num [100000] = {0, };
static int hash_table [10000] = {0, };
static int count = 0;

int main (int argc, char* argv []) {
	int i = 0, j = 0;
	/* Input. */
	if (scanf ("%d", &count));
	while (i < count) {
		if (scanf ("%d", input_num + i));
		hash_table [input_num [i ++]] ++;
	}

	/* Output. */
	while (j < count) {
		if (hash_table [input_num [j]] == 1) {
			printf ("%d", input_num [j]); return 0;
		}
		j ++;
	}

	puts ("None");

	return 0;
}
