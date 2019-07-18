/* Date : 2019/7/18
 * Author : ez
 * Desc :  PAT A 1001
 */

#include <stdio.h>

const char* engnum [] = {
	"zero", "one", "two", "three",
	"four", "five", "six", "seven",
	"eight", "nine", "zero"
};

int main (int argc, char* argv []) {
	char buffer [104] = {0, }, *p;
	int sum = 0, i = 0;
	if (scanf ("%s", buffer)) ;

	p = buffer;
	while (*p) sum += *p ++ - 0x30;

	do {
		buffer [i ++] = (char) (sum % 0xA);
		sum /= 0xA;
	} while (sum);

	while (-- i >= 1)
		printf ("%s ", engnum [(int) buffer [i]]);
	printf ("%s", engnum [(int) buffer [i]]);

	return 0;
}
