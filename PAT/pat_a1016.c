/* Date : 2019/8/6
 * Author : ez
 * Desc :  PAT A 1012
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _rcd {
	char name [24];
	int month; int day;
	int hour; int min;
	/* First low bit denotes on-line(1) 
		 or off-line(0).
	   Second low bit denotes whether 
		 printing(1) or not(0). 
		 From third low bit towards high
		 15 bit will be used to store
		 the calling span. */
	int flag; 
} rcd, *prcd;

#	define RCD_SIZE sizeof (rcd)
#	define _is_online(F) ((F) & 0x01)
#	define _get_span(F) (((F) & 0x3fffc) >> 2)

/* Price for each hour. */
static int price [24] = {0, };
static rcd record [1008];


static int __cmp (const void* _a, const void* _b) {
	int tmp;
	prcd a = (prcd) _a, b = (prcd) _b;
	tmp = strncmp (a -> name, b -> name, 20);
	if (tmp) return tmp;
	tmp = a -> month - b -> month;
	if (tmp)  return tmp;

	tmp = a -> day - b -> day;
	if (tmp)  return tmp;
	tmp = a -> hour - b -> hour;
	if (tmp)  return tmp;
	return a -> min - b -> min;
}

static int calc_output (int _on, int _off, int* _time) {
	int money = 0;
	rcd tmp = record [_on];
	*_time = 0;
	while (tmp.day < record [_off].day || 
			tmp.hour < record [_off].hour ||
			tmp.min < record [_off].min) {
		(*_time) ++; tmp.min ++;
		money += price [tmp.hour];
		if (tmp.min >= 60) { tmp.min = 0; tmp.hour ++; }
		if (tmp.hour >= 24) { tmp.hour = 0; tmp.day ++; }
	}
	return money;
}


static void process (int _n) {
	int on = 0, has_pair, next, 
			time, sum;
	int money;
	next = on;
	while (on < _n) {
		has_pair = 0;
		// Check the pair.
		while (next < _n && ! strncmp (record [on].name, 
					record [next].name, 20)) {
			if (has_pair == 0 && _is_online (record [next].flag))
				has_pair = 1;
			else if (has_pair == 1 && ! _is_online (record [next].flag)) 
				has_pair = 2;
			next ++;
		}

		if (has_pair < 2) { on = next; continue; }

		sum = 0;
		printf ("%s %02d\n", record [on].name, record [on].month);
		// current customer.
		while (on < next) {
			if (_is_online (record [on].flag) && 
					!_is_online (record [on + 1].flag)) {
				if (on + 1 == next) {
					on ++;
					break;
				}
				printf ("%02d:%02d:%02d ", record [on].day, 
						record [on].hour, record [on].min);
				printf ("%02d:%02d:%02d ", record [on + 1].day, 
						record [on + 1].hour, record [on + 1].min);
				money = calc_output (on, on + 1, &time);
				sum += money;
				printf ("%d $%.2f\n", time, money / 100.00);
				on += 2;
			} else on ++;
		}
		printf ("Total amount: $%.2f\n", sum / 100.00);
	}

}

int main (int argc, char* argv []) {
	int n, i = 0;
	char flag [16] = {0, };
	/* Input. */
	while (i < 24) {
		if (scanf ("%d", price + i)); 
		++ i;
	}

	if (scanf ("%d", &n)) ;
	i ^= i;
	while (i < n) {
		if (scanf ("%s %d:%d:%d:%d %s",
					record [i].name, &record [i].month,
					&record [i].day, &record [i].hour,
					&record [i].min, flag)) ;
		record [i].flag = flag [1] == 'n' ? 1 : 0;
		++ i;
	}

	qsort (record, n, RCD_SIZE, __cmp);
	process (n);
	return 0;
}



