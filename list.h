/* The two linear list implementations.
 * 1)	With dynamic array.
 * 2) With linked-list.
 *
 * Author : ez
 * Date :2018/7/3
 */

#ifndef _LIST_H_
#	define _LIST_H_

#include "common.h"

#	define __DEF_ARRAYLIST_LEN__  16


/* The header of a linear list stored
 * with array. The memory shell be 
 * allocated as a dynamic array. */
typedef struct _arraylist {
	anytype* array;
	int capacity;
	int count;
} arraylist, *parraylist;


/* Create a new array list without
 * any input data. It hold a default
 * length array, defined by macro 
 * __DEF_ARRAYLIST_LEN__ . 
 *
 * Return the ptr of new list entity. 
 * Or return NULL while error occured. */
extern parraylist new_arraylist ();


extern parraylist create_arraylist (int);
extern parraylist create_arraylist_by_arr (anytype*, int);

extern void release_arraylist (parraylist, freehook);


/* Insert an element into a separated place.
 * $1  The linear list entity.
 * $2  The element.
 * $3  The separated place to be insert, 
 *		which it ranges from 0 to the value 
 *		of the current [count] of element, the 
 *		head of the list if 0, and the rear 
 *		of the list if [count];
 *
 * Return erronious 0, or successfully return 1. */
extern int insert_arraylist (parraylist, anytype, int);


extern anytype delete_arraylist (parraylist, int);

/* Find the index by an element key.
 *
 * $1  The list entity.
 * $2  The element key.
 * $3  The user-defined comparation function.
 *
 * Return -1 if the key isn't existing. Or 
 * return the first reached index. */
extern int find_arraylist (parraylist, anytype, cmphook);


/* List node for linked-list implementation. */
typedef struct _listnode {
	anytype data;
} listnode, *plistnode;


/* The header of a linear list stored
 * with linked list structure. */
typedef struct _linklist {
	plistnode next;
	int count;
} linklist, *plinklist;

extern plinklist new_linklist ();
extern plinklist create_linklist_by_arr (anytype*, int);

extern void release_linklist (plinklist);
extern int insert_linklist (plinklist, anytype, int);
extern anytype delete_linklist (plinklist, int);
extern int find_linklist (plinklist, anytype, cmphook);


#endif // ~ _LIST_H_

