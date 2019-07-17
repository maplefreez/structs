/*
 * Author : ez
 * Date : 2019/7/16
 * Desc : PAT A 1073, PAT B 1024
 */
#include <stdio.h>

int main (int argc, char* argv []) {
	char input [10008] = {0, }, *p, *ep;
	int /* slen = 0, */ exp = 0, i;
	
	if (scanf ("%s", input)) {}
	// slen = strlen (input);
	
	if (input [0] == '-') putchar ('-');

	p = input;
	while (*p && *p != 'E') p ++;
	for (ep = p + 2; *ep; ++ ep)
		exp = exp * 10 + *ep - '0';

	/* Output */
	if (! exp) {
		printf ("%s", input + 1);
		return 0;
	}

	if (*(p + 1) == '-') {
		printf ("%s", "0.");
		i = exp - 1; 
		while (i -- > 0) putchar ('0');
		putchar (input [1]);

		ep = input + 3;
		while (ep < p) putchar (*ep ++);
	} else {
		ep = input + 1;
		i = exp + 1;
		while (ep < p && i > 0) {
			if (*ep == '.') 
				{ ep ++; continue; }
			putchar (*ep ++);
			i --;
		}

		if (ep < p) {
			putchar ('.');
			while (ep < p) putchar (*ep ++);
		}
		
		while (i -- > 0) putchar ('0');
	}

	return 0;
}
