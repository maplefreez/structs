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
 * __DEF_ARRAYLIST_LEN__ . */
extern parraylist new_arraylist ();
extern parraylist create_arraylist (int);
extern parraylist create_arraylist_by_arr (anytype*, int);

extern void release_arraylist (parraylist);
extern int insert_arraylist (parraylist, anytype, int);
extern anytype delete_arraylist (parraylist, int);
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

extern plinklist new_arraylist ();
extern plinklist create_linklist_by_arr (anytype*, int);

extern void release_linklist (plinklist);
extern int insert_linklist (plinklist, anytype, int);
extern anytype delete_linklist (plinklist, int);
extern int find_linklist (plinklist, anytype, cmphook);


#endif // ~ _LIST_H_

