#ifndef _STACK_H_
#	define _STACK_H_

#	define DEFAULT_STACK_CAPACITY  (0x10)

typedef void* anytype;

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

extern int arrstack_isempty (parrstack);

#endif // ~ _STACK_H_

