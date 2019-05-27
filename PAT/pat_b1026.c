/* Date : 2018/12/29
 * Author : ez
 * Desc :  PAT B 1026
 */

#include <stdio.h>
#	define clk_tck 100
int main (int argc, char* argv []) {
	int c1, c2, diff;
	scanf ("%d %d", &c1, &c2);
	diff = c2 - c1;
	diff = diff % clk_tck >= 50 ? 
		diff / 100 + 1 : diff / 100;
	printf ("%02d:%02d:%02d\n", diff / 3600, 
			diff % 3600 / 60, diff % 60);
	return 0;
}

