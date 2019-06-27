/* Date : 2019/6/27
 * Author : ez
 * Desc :  PAT A 1011
 */

#include <stdio.h>

struct _name {
	char name [0x20];
} unlock, lock, input;


int main (int argc, char* argv []) {
	unsigned long long temp;
	unsigned long long earliest = 246060UL, 
										latest = 0UL;
	int hour, min, sec, n;

	scanf ("%d", &n);
	while (n -- > 0) {
		scanf ("%s", input.name);
		/* Sign in */
		scanf ("%d:%d:%d", &hour, &min, &sec);
		temp = hour*10000 + min*100 + sec;
		if (temp < earliest) {
			earliest = temp;
			unlock = input;
		}

		/* Sign out */
		scanf ("%d:%d:%d", &hour, &min, &sec);
		temp = hour*10000 + min*100 + sec;
		if (temp > latest) {
			latest = temp;
			lock = input;
		}
	}

	printf ("%s %s", unlock.name, lock.name);

	return 0;
}
