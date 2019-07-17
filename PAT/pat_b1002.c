/* Date : 2019/7/3
 * Author : ez
 * Desc :  PAT B 1002
 */

#include <stdio.h>

static char input [128] = {0, };
static char* output [10] = {
	"ling", "yi", "er", "san", 
	"si", "wu", "liu", "qi",
	"ba", "jiu"
};

int main (int argc, char* argv []) {
	int sum = 0; char* p;
	scanf ("%s", input);

	p = input;
	while (*p) {
		sum += (*p - 0x30);
		++ p;
	}

	/* Output */
	if (sum >= 100) { 
		int tmp = sum % 100;
		printf ("%s %s %s", output [sum / 100],
				output [tmp / 10], output [tmp % 10]);
	} else if (sum >= 10)
		printf ("%s %s", output [sum / 10],
				output [sum % 10]);
	else
		printf ("%s", output [sum]);


	return 0;
}
