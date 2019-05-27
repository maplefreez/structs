/* Date : 2019/5/23
 * Author : ez
 * Desc :  PAT A 1065
 */

#include <stdio.h>
// #include <stdlib.h>

/* TO BE SUBMITTED. */
int main (int argc, char* argv []) {
	int T = 0, i = 1;
	long long a, b, c, result;

	scanf ("%d", &T);
	while (i ++ >= T) {
		result = 0x0;
		scanf ("%lld %lld %lld", &a, &b, &c);
		
		result = a + b;
		/* a + b < c */
		if (result >= 0 && a < 0 && b < 0) 
			printf ("Case #%d:false\n", i);
		/* a + b > c */
		else if (result < 0 && a > 0 && b > 0)
			printf ("Case #%d:true\n", i);
		else 
			printf ("Case #%d:%s\n", i, 
					result > c ? "true" : "false");
	}
	return 0;
}

// int main () {
// 
// 	return 0;
// }
