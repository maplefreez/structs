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

/* Delete an element from existing list entity.
 * $1  The array list entity ptr.
 * $2  The index of element to be deleted.
 * 
 * Return the deleted element if successful.
 * Or return NULL if error. 
 * 
 * The $2 parameter should range from 0 to length - 1. Or
 * NULL will be returned directly. */
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
typedef struct _listnode listnode, *plistnode;

typedef struct _listnode {
	plistnode next;
	anytype data;
} listnode, *plistnode;


/* The header of a linear list stored
 * with linked list structure. */
typedef struct _linklist {
	plistnode first;
	int count;
} linklist, *plinklist;


/* Create a new linked-list without any
 * element. 
 *
 * Return the pointer to the new one. 
 * Return NULL if there remains no memory. */
extern plinklist new_linklist ();


/* Create a linked-list by inputing anytype array.
 * $1  Array used to create list, if $1 NULL, nothing
 *      shell be done and return NULL instantly.
 * $2  The length of $1. The function access the number
 *      of elements in $1 by this parameter.
 * 
 * Return new linked-list entity ptr successfully.
 * Or return NULL. */
extern plinklist create_linklist_by_arr (anytype*, int);


/* Release a linked-list entity.
 * $1  linked-list entity ptr to be released. Return instantly
        if it's NULL.
 * $2  A customer-defined free hook for 'anytype' structure.
 *      If NULL is passed, the function invokes the default
 *      implementation (Doing nothing). */
extern void release_linklist (plinklist, freehook);


/* Insert an element into a separated place.
 * $1  The linked list entity.
 * $2  The element.
 * $3  The separated place to be insert, 
 *		which ranges from 0 to the value 
 *		of the current [count] of element, the 
 *		head of the list if 0, and the rear 
 *		of the list if [count]; ????? TODO...
 *
 * Return erronious 0, or successfully return 1. */
extern int insert_linklist (plinklist, anytype, int);

/* Delete an element with its index from a linked-list 
 * entity. 
 * $1  Linked-list to be manipulated.
 * $2  The index of removed element. It ranges from 
 *      0 to the value plus -1 of the [count] field.
 *   TODO...
 * 
 * Return the element data if successful. Or return NULL. */
extern anytype delete_linklist (plinklist, int);

extern int find_linklist (plinklist, anytype, cmphook);


#endif // ~ _LIST_H_

