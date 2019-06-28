/* Date : 2019/6/27
 * Author : ez
 * Desc :  PAT A 1036
 */

#include <stdio.h>

struct studinfo {
	char name [0x20];
	char id [0x20];
} temp, 
	female = { "#", "#" }, 
	male = { "#", "#" };

int main (int argc, char* argv []) {
	int n; char gender; 
	short fmax, mmin, score;

	scanf ("%d", &n);
	fmax = -1, mmin = 101;
	while (n -- > 0) {
		scanf ("%s %c %s %hd", temp.name, &gender, 
				temp.id, &score);
		if (gender == 'F' && fmax < score) {
					fmax = score;
					female = temp;
		} else if (gender == 'M' && mmin > score) {
					mmin = score;
					male = temp;
		}
	}

	n ^= n;
	if (female.name [0] != '#')
		printf ("%s %s\n", female.name, female.id);
	else {
		puts ("Absent");
		n = 1;
	}

	if (male.name [0] != '#')
		printf ("%s %s\n", male.name, male.id);
	else {
		puts ("Absent");
		n = 1;
	}

	if (n)
		puts ("NA");
	else
		printf ("%hd", fmax - mmin);

	return 0;
}

