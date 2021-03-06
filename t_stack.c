#include "stack.h"
#include <assert.h>
#include <stdlib.h>


/****** Pre-defination for test suits. ******/
static void t_arrstack_create ();
static void t_arrstack_create_by_arr ();
static void t_arrstack_push ();
static void t_arrstack_push1 ();
static void t_arrstack_release ();
static void t_arrstack_pop ();
static void t_arrstack_peak ();

static void _free_hook1 (const void*);
/* We use this array to store freed element
 * on testing release function. */
static int _freed_elm [1024] = {0, };
static int _arr_index = 0;


/* Main test entry. */
int main (int argc, char* argv []) {
	t_arrstack_create ();
	t_arrstack_create_by_arr ();
	t_arrstack_release ();
	t_arrstack_push ();
	t_arrstack_push1 ();
	t_arrstack_pop ();
	t_arrstack_peak ();
	return 0;
}


/******* Implementation for each test suit. ******/

static void t_arrstack_create () {
	/* 1024 stack. */
	parrstack stack;
	{
		stack = arrstack_create (1024);
		assert (stack != NULL);
		assert (stack -> top == 0);
		assert (stack -> base != NULL);
		assert (stack -> capacity == 1024);
		arrstack_release (stack, NULL);
	}

	/* 0 stack. */
	{
		stack = arrstack_create (0);
		assert (stack != NULL);
		assert (stack -> top == 0);
		assert (stack -> base != NULL);
		assert (stack -> capacity == DEFAULT_STACK_CAPACITY);
		arrstack_release (stack, NULL);
	}

	/* -3232 stack. */
	{
		stack = arrstack_create (-3232);
		assert (stack != NULL);
		assert (stack -> top == 0);
		assert (stack -> base != NULL);
		assert (stack -> capacity == DEFAULT_STACK_CAPACITY);
		arrstack_release (stack, NULL);
	}

}


static void t_arrstack_create_by_arr () {
	{ // 0x01 
		anytype temp [16] = {0, 1, 2, };
		assert (NULL == arrstack_create_by_arr (NULL, 0));
		assert (NULL == arrstack_create_by_arr (NULL, 512));
		assert (NULL == arrstack_create_by_arr (temp, 0));
		assert (NULL == arrstack_create_by_arr (temp, -16));
		assert (NULL == arrstack_create_by_arr (NULL, -2048));
	}

}


static void t_arrstack_push () {
	int i = 0;
	parrstack stack = arrstack_create (128);
	assert (stack != NULL);

	/* Note: Because the element pointer must
	 * not be NULL, so if we push a integer 
	 * zero, it will be treated as NULL. so
	 * we ignore this element for testing. 
	 *
	 * The input sequence is generated by:
	 * f(n) = n + 1, n belongs to [0, 64) */
	for (; i < 64; ++ i)
		arrstack_push (stack, (void*) (i + 1));
	
	assert (stack -> top == 64);
	assert (stack -> capacity == 128);

	for (i = 0; i < 64; ++ i)
		assert ((stack -> base) [i] == (void*) (i + 1));

	arrstack_release (stack, NULL);
}


static void t_arrstack_push1 () {
	int i = 0;
	parrstack stack;

	/* 0x1*/
	{
		stack = arrstack_create (8);
		assert (stack != NULL);

		for (i = 1; i <= 8; ++ i) {
			arrstack_push (stack, (void*) (i));
			assert (stack -> top == i);
			assert (stack -> capacity == 8);
		}

		/* trigger memory reallocation. */
		arrstack_push (stack, (void*) 256);
		assert (stack -> top == 9);
		assert (stack -> capacity == 16);
		arrstack_release (stack, NULL);
	}

	/* 0x2, Input only one element */
	{
		stack = arrstack_create (8);
		assert (stack -> top == 0);
		assert (stack -> capacity == 8);

		arrstack_push (stack, (void*) 100);
		assert (stack -> top == 1);
		assert (stack -> capacity == 8);
		arrstack_release (stack, NULL);
	}

}


/* Used by release function testing. */
static void _free_hook1 (const void* _e) {
	_freed_elm [_arr_index ++] = (int) _e;
}

static void t_arrstack_release () {
	int i = 0, n;
	_arr_index = 0;
	parrstack stack = arrstack_create (64);
	assert (stack != NULL);

	/* Sequence : f(n) = n * 2 + 32 */
	for (i = 1; i <= 64; ++ i)
		arrstack_push (stack, (void*) ((i << 1) + 32));
	
	assert (stack -> top == 64);
	assert (stack -> capacity == 64);

	arrstack_release (stack, _free_hook1);
	/* That is to say, _free_hook1() have
	 * been invoked 64 times. */
	assert (_arr_index == 64);
	assert (_freed_elm [_arr_index]== 0);

	/* To test each element being freed by
	 * user-defined callback. 
	 *
	 * Note: we have to reversed the sequence 
	 * generated by f(n) = n * 32 + 32 due to 
	 * the implementation of stack release 
	 * function. */
	for (i = 0, n = 64; i < 64; ++ i, -- n)
		assert (_freed_elm [i] == ((n << 1) + 32));
}



static void t_arrstack_pop () {
	int i = 0;
	parrstack stack;
	anytype x;

	/* 0x1 Pop an empty stack. */
	{
		stack = arrstack_create (0);
		assert (stack != NULL);
		assert (stack -> top == 0);
		x = arrstack_pop (stack);

		assert (x == NULL);
		assert (stack -> top == 0);
		arrstack_release (stack, NULL);
	}

	/* 0x2 Pop a full stack. */
	{
		stack = arrstack_create (8);
		assert (stack != NULL);

		/* Skip integer 0. */
		for (i = 1; i <= 8; ++ i)
			arrstack_push (stack, (void*) (i));

		assert (stack -> top == 8);
		assert (stack -> capacity == 8);

		x = arrstack_pop (stack);
		assert (x != NULL && x == (void*) 8);
		assert (stack -> top == 7);
		assert (stack -> capacity == 8);

		arrstack_release (stack, NULL);
	}

	/* 0x3  Pop a reallocated stack. */
	{
		stack = arrstack_create (4);
		assert (stack != NULL);

		/* Skip integer 0. */
		for (i = 1; i <= 5; ++ i)
			arrstack_push (stack, (void*) (i));

		assert (stack -> top == 5);
		assert (stack -> capacity == 8);

		x = arrstack_pop (stack);
		assert (x != NULL && x == (void*) 5);
		assert (stack -> top == 4);
		assert (stack -> capacity == 8);

		arrstack_release (stack, NULL);
	}
	
	/* 0x4  Pop NULL. */
	{
		x = arrstack_pop (NULL);
		assert (x == NULL);
	}

}


static void t_arrstack_peak () {
	int i = 0;
	parrstack stack;
	anytype x;

	/* 0x1 Get the top of an 
	 *     empty stack. */
	{
		stack = arrstack_create (0);
		assert (stack != NULL);
		assert (stack -> top == 0);
		x = arrstack_peak (stack);

		assert (x == NULL);
		assert (stack -> top == 0);
		arrstack_release (stack, NULL);
	}

	/* 0x2 Get the top of a 
	 *     full stack. */
	{
		stack = arrstack_create (8);
		assert (stack != NULL);

		/* Skip integer 0. */
		for (i = 1; i <= 8; ++ i)
			arrstack_push (stack, (void*) (i));

		assert (stack -> top == 8);
		assert (stack -> capacity == 8);

		x = arrstack_peak (stack);
		assert (x != NULL && x == (void*) 8);
		assert (stack -> top == 8);
		assert (stack -> capacity == 8);

		arrstack_release (stack, NULL);
	}

	/* 0x3  Get the top of a 
	 *			reallocated stack. */
	{
		stack = arrstack_create (4);
		assert (stack != NULL);

		/* Skip integer 0. */
		for (i = 1; i <= 5; ++ i)
			arrstack_push (stack, (void*) (i));

		assert (stack -> top == 5);
		assert (stack -> capacity == 8);

		x = arrstack_peak (stack);
		assert (x != NULL && x == (void*) 5);
		assert (stack -> top == 5);
		assert (stack -> capacity == 8);

		arrstack_release (stack, NULL);
	}
	
	/* 0x4  Pop NULL. */
	{
		x = arrstack_peak (NULL);
		assert (x == NULL);
	}
}



