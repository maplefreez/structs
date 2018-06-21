#ifndef _SORT_H_
#	define _SORT_H_

#include "common.h"

/* Straight insert sort algorithm */
extern anytype* straight_insertsort (anytype*, int, cmphook);

/* Binary insert sort algorithm */
extern anytype* binary_insertsort (anytype*, int, cmphook);

#endif // ~ _SORT_H_
