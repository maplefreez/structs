/* Date : 2019/6/26
 * Author : ez
 * Desc :  PAT B 1004
 */

#include <stdio.h>

struct _tempinfo {
	char name [0x10]; char num [0x10];
	short score;
} tempinfo = { "", "", 0 }, max, min;

int main (int argc, char* argv []) {
	int count;
	max.score = -1;
	min.score = 101;

	/* Process input. */
	scanf ("%d", &count);
	while (count -- > 0) {
		scanf ("%s %s %hd", tempinfo.name, tempinfo.num,
				&tempinfo.score);
		if (tempinfo.score > max.score)
			max = tempinfo;
		if (tempinfo.score < min.score)
			min = tempinfo;
	}

	/* Max */
	printf ("%s %s\n", max.name, max.num);
	/* Min */
	printf ("%s %s\n", min.name, min.num);

	return 0;
}

