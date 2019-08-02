/* Date : 2019/7/18
 * Author : ez
 * Desc :  PAT A 1001
 */

#include <stdio.h>

typedef struct _user {
	char name [0x10];
	char pwd [0x10];
} user, *puser;

user output [1001];

static int judge (puser _u) {
	char *p; int x = 0;
	p = _u -> pwd;
	while (*p) {
		switch (*p) {
			case '1':
				*p ++ = '@'; x = 1; continue;
			case '0':
				*p ++ = '%'; x = 1; continue;
			case 'l':
				*p ++ = 'L'; x = 1; continue;
			case 'O':
				*p ++ = 'o'; x = 1; continue;
			default: 
				p ++; continue;
		}
	}
	return (x);
}


int main (int argc, char* argv []) {
	int n, modified = 0, i = 0;
	if (scanf ("%d", &n)) ;
	while (i ++ < n) {
		if (scanf ("%s %s", output [1000].name, output [1000].pwd)) ;
		if (judge (output + 1000)) {
			output [modified ++] = output [1000];
		}
	}

	if (modified)
		printf ("%d\n", modified);
	else
		printf ("There %s %d %s and no account is modified", 
				n > 1 ? "are" : "is",
				n, n > 1 ? "accounts" : "account");

	i = 0;
	while (i < modified) {
		printf ("%s %s\n", output [i].name, output [i].pwd);
		++ i;
	}
	return 0;
}

