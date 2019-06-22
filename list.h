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

/* Reverse the elements in the special array-list.
 * $1  The linear list entity.
 * Return $1 if successful, else return NULL. 
 *
 * Note: A NULL list ptr causes a NULL returning value. */
extern parraylist reverse_arraylist (parraylist);


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


/* Delete all the nodes in an array list entity, that
 * its data domain equals to the key parameter, $2.
 *
 * $1  An Array-list to be manipulated.
 * $2  The key of the node to be searched and deleted.
 * $3  The function used to compare two keys.
 * $4  A customer-defined free hook for 'anytype' structure.
 *      If NULL is passed, the function invokes the default
 *      implementation (Doing nothing). 
 * Note: if $1 is NULL, the function directly returns. */
extern void delete_arraylist_key (parraylist, anytype, 
		cmphook, freehook);


/* Remove the same element when there exists multiple
 * elements in an array-list.
 * $1  An array-list to be manipulated.
 * $2  The function used to compare two keys.
 * $3  A customer-defined free hook for 'anytype' structure.
 *      If NULL is passed, the function invokes the default
 *      implementation (Doing nothing).
 * Note: If $1 is NULL, the function directly returns. */
extern void remove_same_arraylist (parraylist, cmphook, freehook);


/* Find the index by an element key.
 *
 * $1  The list entity.
 * $2  The element key.
 * $3  The user-defined comparation function.
 *
 * Return -1 if the key isn't existing. Or 
 * return the first reached index. */
extern int find_arraylist (parraylist, anytype, cmphook);

/* Merge two ordered array-list.
 * Note: The function assume the 2 input array-list is 
 * with ascentive order. And they 2 must hold at lest
 * one element.
 * 
 * $1  The first list entity.
 * $2  The second list entity.
 * $3  The function used to compare two keys.
 * Return a new array-list entity if successful, else 
 * return NULL. */
extern parraylist merge_arraylist (parraylist, parraylist, cmphook);


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

/* A function prototype for traversing 
   each element in a linked-list. */
typedef void (*llist_visitf) (plistnode);


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


/* Create a linked-list by inputing anytype array. Note
 * this implementation create a list entity with reversed  
 * order input array.
 * $1  Array used to create list, if $1 NULL, nothing
 *      shell be done and return NULL instantly.
 * $2  The length of $1. The function access the number
 *      of elements in $1 by this parameter.
 * 
 * Return new linked-list entity ptr successfully.
 * Or return NULL. */
extern plinklist create_linklist_by_arr_revr (anytype*, int);


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
 *		of the list if [count];
 *
 * Return erronious 0, or successfully return 1. */
extern int insert_linklist (plinklist, anytype, int);


/* Delete an element with its index from a linked-list 
 * entity. 
 * $1  Linked-list to be manipulated.
 * $2  The index of removed element. It ranges from 
 *      0 to the value plus -1 of the [count] field.
 * 
 * Return the element data if successful. Or return NULL. */
extern anytype delete_linklist (plinklist, int);


/* Delete all the nodes in a linked list entity, that
 * its data domain equals to the key parameter, $2. This
 * is a recursive implementation.
 *
 * $1  Linked-list to be manipulated.
 * $2  The key of the node to be searched and deleted.
 * $3  The function used to compare two keys.
 * $4  A customer-defined free hook for 'anytype' structure.
 *      If NULL is passed, the function invokes the default
 *      implementation (Doing nothing). 
 * 
 * Note: if $1 is NULL, the function directly return. */
extern void delete_linklist_key_recr (
		plinklist, anytype, 
		cmphook, freehook);


/* Delete all the nodes in a linked list entity, that
 * its data domain equals to the key parameter, $2.
 *
 * $1  Linked-list to be manipulated.
 * $2  The key of the node to be searched and deleted.
 * $3  The function used to compare two keys.
 * $4  A customer-defined free hook for 'anytype' structure.
 *      If NULL is passed, the function invokes the default
 *      implementation (Doing nothing). 
 * Note: if $1 is NULL, the function directly return. */
extern void delete_linklist_key (plinklist, anytype,
		cmphook, freehook);

/* Get element by index. The index ranges from 1 to 
 * count.
 * $1  The linked-list ptr.
 * $2  The index at which it's data is returned. 
 *
 * Return... */
extern anytype get_linklist_index (plinklist, int);


/* Get the maximum element in a linked-list.
 * $1  The linked-list ptr.
 * $2  The comparation function ptr.
 * 
 * Return the data domain of the maximum node, 
 * or return NULL if $1 is NULL. 
 *
 * Note: As to an empty linked-list, it 
 * directly returns NULL. */
extern anytype get_linklist_max (plinklist, cmphook);

/* Get the minimum element in a linked-list.
 * $1  The linked-list ptr.
 * $2  The comparation function ptr.
 * 
 * Return the data domain of the minimum node, 
 * or return NULL if $1 is NULL. 
 *
 * Note: As to an empty linked-list, it 
 * directly returns NULL. */
extern anytype get_linklist_min (plinklist, cmphook);


/* Find the first match element by key. Caller should 
 * pass the function ptr comparing between each element
 * and key, or the function uses default implementation,
 * that is, comparing only through 'key == node -> data'
 * statement.
 * 
 * $1  List entity ptr.
 * $2  The key to match.
 * $3  The comparation function ptr.
 *
 * Return the first match element index. Or return -1 if
 * there is no match element. 
 * Note: A NULL list ptr conducts to -1 
 * returning directly. */
extern int find_linklist (plinklist, anytype, cmphook);

/* Traverse each element in a linked-list.
 * $1  List entity ptr.
 * $2  The accessor function difined by user.
 *
 * Note: If $1 or $2 is NULL, nothing will be done. The
   function exits directly. */
extern void foreach_linklist (plinklist, llist_visitf);


/* Traverse each element of a linked-list with 
 * reversed order. It's a recursive implementation.
 *
 * $1  List entity ptr.
 * $2  The accessor function difined by user.
 *
 * Note: If $1 or $2 is NULL, nothing will be done. The
   function exits directly. */
extern void foreach_linklist_revr_recr (plinklist, llist_visitf);


/* Sort the element in ascending order.
 * 
 * $1  List entity ptr.
 * $2  The comparation function ptr. */
extern void sort_linklist (plinklist, cmphook);


extern void trim_linklist ();


#endif // ~ _LIST_H_

