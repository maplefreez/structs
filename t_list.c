#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"


/****** Pre-defination for test suits. ******/
static void t_arraylist_insert ();
static void t_linklist_insert ();
static void __def_free_hook (const void*);



/* Main test entry. */
int main (int argc, char* argv []) {
	t_arraylist_insert ();
	t_linklist_insert ();
	return 0;
}



/******* Implementation for each test suit. ******/
static void t_arraylist_insert () {
	int data [] = {
		10, 20, 30, 40,
		50, 60, 70, 80,
		90, 100, 200, 300
	};

	int count = sizeof (data) / sizeof (int);
	int i = 0;

	parraylist list = NULL;

	/* 0x01 */
	{
		list =create_arraylist (count + 4);
		assert (list);
		assert (list -> capacity == (count + 4));
		assert (list -> count == 0);

		while (i < count) {
			assert (
				insert_arraylist (list, (anytype) data [i], i)
			);
			assert (list -> count == (++ i));
		}
		
		/* Assert each element. */
		i = 0;
		while (i < count) {
			assert ((anytype) (list -> array [i]) == 
					(anytype) data [i]);
			i ++;
		}

		release_arraylist (list, NULL);
	}


}



static void t_linklist_insert () {
	int flag;
	plinklist list;
	plistnode ptr;


	{
		/* 0x0. Add to the first index. */
		list = new_linklist ();
		assert (list && list -> count == 0
				&& list -> first == NULL);

		flag = insert_linklist (list, (anytype) 32, 0);
		assert (flag);

		assert (list -> count == 1 &&
				list -> first != NULL);
		assert (list -> first -> data == (anytype) 32);
		assert (list -> first -> next == NULL);

		/* 0x2. Append to the rear. */
		flag = insert_linklist (list, (anytype) 0xFFFFFFFF, 1);
		/* First element. */
		assert (flag);
		assert (list -> count == 2 &&
				list -> first != NULL);

		/* Second element (The last one). */
		ptr = list -> first -> next;
		assert (ptr && ptr -> next == NULL);
		assert (ptr -> data == (anytype) 0xFFFFFFFF);

		// release_linklist (list, __def_free_hook);
	}


}


static void __def_free_hook (const void* x) 
	{ /* Doing nothing. */ }


