/*
 * Stack implementation, with array approach.
 *
 * Author : ez
 * Date : 2018/6/9
 *
 * +-+-+-+-+-+
 * |s|t|a|c|k|
 * +-+-+-+-+-+
 *					                                
 */


#ifndef _STACK_H_
#	define _STACK_H_

#include <stdlib.h>
#include "common.h"

#	define DEFAULT_STACK_CAPACITY  (0x10)

// typedef void* anytype;

/* A simpe stack structure implemented by
 * an array. */
typedef struct _arrstack {
	/* The array to store element. */
	anytype* base;

	/* The top index of the stack, 
	 * whose scope's [0, capacity - 1];
	 * We specialize it the next position 
	 * to be pushed. And 0 represents empty
	 * stack, while (capacity - 1) for full
	 * stack. */
	int top;

	/* The total length of array. */
	size_t capacity;
} arrstack, *parrstack;


/* Create a new empty stack with 
 * $1 realloced space. 
 *
 * $1  The maximum space of stack. It
 *    must be a positive integer, an
 *    invalid input is treated as same 
 *    as macro DEFAULT_STACK_CAPACITY.
 *
 * Return the ptr of new stack if successful.
 * Otherwise return NULL. */
extern parrstack arrstack_create (int);

/* Push one element into stack. If $1 or $2
 * is NULL, nothing will be done in this
 * function. Note: if the stack is full, it
 * will automatically realloc enough space.
 */
extern void arrstack_push (parrstack, anytype);

/* Pop the top element pointer and removed 
 * it from a stack. If the stack is empty, 
 * return NULL.
 *
 * $1  The stack pointer. If input is NULL,
 *      return NULL. 
 *
 * Return the top element pointer. */
extern anytype arrstack_pop (parrstack);


/* Return the top element but donot remove it.
 * $1  The stack ptr. 
 * 
 * If $1 is NULL or it's an empty stack, 
 * return NULL.*/
extern anytype arrstack_peak (parrstack);


/* Test whether the stack has no element.
 *
 * $1  The stack pointer.
 *
 * Return : 
 * Empty -> 1
 * Not empty -> 0
 * Note: The $1 must not be NULL, cuz the
 * function cannot assert this condition. */
extern int arrstack_isempty (parrstack);


/* Release a stack. Memory of each element 
 * shell be freed by user-defined callback.
 *
 * $1  The stack pointer.
 * $2  The user-defined callback. 
 *
 * Note: Nothing will be done when $1 is NULL.
 * If user input a NULL callback, the function
 * invokes an inner default implementation one,
 * that's, doing NOTHING. */
extern void arrstack_release (parrstack, freehook);

#endif // ~ _STACK_H_


