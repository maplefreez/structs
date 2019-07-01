/* Date : 2019/6/26
 * Author : ez
 * Desc :  PAT B 1028
 */

#include <stdio.h>

struct _person {
	char name [0x8];
	unsigned long long birth;
} person = { "", 0L }, eldest, youngest;

const unsigned long long maxage = 18140906UL;
const unsigned long long minage = 20140906UL;

int main (int argc, char* argv []) {
	int count, year, month, day, i = 0;
	unsigned long long birth;

	eldest.birth = minage + 1;
	youngest.birth = maxage - 1;

	scanf ("%d", &count);
	while (count -- > 0) {
		scanf ("%s %d/%d/%d", person.name, 
				&year, &month, &day);
		person.birth = birth = year*10000 + month*100 + day;

		if (birth >= maxage && birth <= minage) {
			i ++;
			/* Eldest. */
			if (birth < eldest.birth) 
				eldest = person;
			/* Youngest. */
			if (birth > youngest.birth) 
				youngest = person;
		}
	}

	if (i)
		printf ("%d %s %s\n", i, eldest.name, youngest.name);
	else
		puts ("0");

	return 0;
}
