/* Date : 2019/7/3
 * Author : ez
 * Desc :  PAT B 1009
 */

#include <stdio.h>


// int main (int argc, char* argv []) {
// 	int num = 0;
// 	char wards [96][96];
// 
// 	while (EOF != scanf ("%s", wards [num ++]));
// 
// 	while (-- num >= 1)
// 		printf ("%s ", wards [num]);
// 	printf ("%s", wards [num]);
// 
// 	return 0;
// }

int main (int argc, char* argv []) {
	int num = 0, i;
	char wards [96] [96], str [96], *p;
	if (scanf ("%s", str)) ;
	p = str;

	i = 0;
	while (*p) {
		if (*p != ' ')
			wards [num] [i ++] = *p;
		else {
			wards [num] [i] = '\0';
			i ^= i;
			num ++;
		}
		p ++;
	}

	while (-- num >= 1)
		printf ("%s", wards [num]);
	printf ("%s", wards [num]);

	return 0;
}

