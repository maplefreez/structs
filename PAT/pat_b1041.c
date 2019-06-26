/* Date : 2019/6/26
 * Author : ez
 * Desc :  PAT B 1041
 */

#include <stdio.h>

struct _studinfo {
	int testno; int examno;
	unsigned long long serial;
} studinfo [1024];


int main (int argc, char* argv []) {
	int count; int i = 0;
	/* Process input. */
	scanf ("%d", &count);
	while (i ++ < count) {
		int testno, examno;
		unsigned long long serial;

		scanf ("%lld %d %d", &serial, &testno, &examno);
		studinfo [testno].serial = serial;
		studinfo [testno].examno = examno;
	}

	/* Search. */
	i ^= i;
	scanf ("%d", &count);
	while (i ++ < count) {
		int search;
		scanf ("%d", &search);
		printf ("%lld %d\n", studinfo [search].serial, 
				studinfo [search].examno);
	}

	return 0;
}
