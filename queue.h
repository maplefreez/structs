/* Author : ez
 * Date : 2018/12/29
 *
 */

#ifndef _QUEUE_H_
#	define _QUEUE_H_

#include "common.h"

#	define __DEF_QUEUE_INIT_LEN__  16

/* A simple circle queue definition whose
 * element stored in array. */
typedef struct _cqueue {
	anytype* array;
	int rear; int head;
} cqueue, *pcqueue;


extern pcqueue new_cqueue ();
extern pcqueue create_cqueue (int);
extern pcqueue create_cqueue_by_arr (anytype*, int);
extern int isempty_cqueue (pcqueue);
extern int isfull_cqueue (pcqueue);
extern int count_cqueue (pcqueue);
extern anytype enqueue_cqueue (pcqueue, anytype);
extern anytype dequeue_cqueue (pcqueue);
extern void release_cqueue (pcqueue);

#endif // ~ _QUEUE_H_
