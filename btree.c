#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "btree.h"
#include "stack.h"


static void _default_visit_func (pbtnode);
static void _bt_pretraversal (pbtree, bt_visitf);
static void _bt_posttraversal (pbtree, bt_visitf);
static void _bt_inordertraversal (pbtree, bt_visitf);

static pbtree _bt_create_pre_inorder (char**, char*, char*);
static pbtree _bt_create_post_inorder (char**, char*, char*);

/* Create a new tree by inputing data list
 * and it's length. The list shell be supposed
 * as a preorder traversal sequency.
 * $1  The data list. 
 * $2  The length of $1. 
 * 
 * Return the new tree pointer while successful. 
 * Or NULL if $1 is NULL, empty or another unexpected
 * error (e.g. out of memory). */
// pbtree bt_create (void** _data, int _len) {
	// TODO...
// }


pbtnode bt_create_node (void* _data) {
	pbtree ret = NULL;
	if (_data) {
		ret = (pbtnode) malloc (sizeof (btnode));
		if (! ret) return NULL;

		/* Initialize fields. */
		ret -> left = ret -> right = NULL;
		ret -> data = _data;
	}
	return ret;
}

void bt_pretraversal (pbtree _t, bt_visitf _func) {
	/* Use our default traversal implementation. */
	if (! _func) _func = _default_visit_func;
	_bt_pretraversal (_t, _func);
}

static void _bt_pretraversal (pbtree _t, bt_visitf _func) {
	if (_t != NULL) {
		_func (_t);
		_bt_pretraversal (_t -> left, _func);
		_bt_pretraversal (_t -> right, _func);
	}
}

void bt_posttraversal (pbtree _t, bt_visitf _func) {
	if (! _func) _func = _default_visit_func;
	_bt_posttraversal (_t, _func);
}

static void _bt_posttraversal (pbtree _t, bt_visitf _func) {
	if (_t != NULL) {
		_bt_posttraversal (_t -> left, _func);
		_bt_posttraversal (_t -> right, _func);
		_func (_t);
	}
}


void bt_inordertraversal1 (pbtree _t, bt_visitf _func) {
	parrstack s = NULL; pbtnode ptr = _t;
	if (! ptr) return;
	if (! _func) _func = _default_visit_func;

	s = arrstack_create (INIT_STACK_LEN);
	if (! s) return; /* Doing nothing. */

	/* Visit. */
	while (ptr || ! arrstack_isempty (s)) {
		if (ptr) {
			/* Turn left left left... 
			 * till the end. */
			arrstack_push (s, ptr);
			ptr = ptr -> left;
		} else {
			/* Push right child. */
			ptr = arrstack_pop (s);
			_func (ptr);
			ptr = ptr -> right;
			// arrstack_push (s, ptr -> right);
		}
	}

	arrstack_release (s, NULL);
}


void bt_inordertraversal (pbtree _t, bt_visitf _func) {
	if (! _func) _func = _default_visit_func;
	_bt_inordertraversal (_t, _func);
}


void bt_leveltraversal (pbtree _t, bt_visitf _func) {
	/* TODO Sorry for no queue structure available. */
	// pqueue q;
	// pbtnode ptr;
	// 
	// if (_t) {
	// 	if (! _func) _func = _default_visit_func;
	// 	q = queue_create ();
	// 	ptr = (pbtnode) _t;
	// 	queue_enqueue (q, ptr);

	// 	/* Start traversing. */
	// 	while (! queue_isempty (q)) {
	// 		pbtnode x = (pbtnode) queue_dequeue (q);
	// 		_func (x);
	// 		if (x -> left) queue_enqueue (q, x -> left);
	// 		if (x -> right) queue_enqueue (q, x -> right);
	// 	}
	// 	
	// }
}

void bt_release (pbtree _t, bt_freef _func) {
	if (_t) {
		bt_release (_t -> left, _func);
		bt_release (_t -> right, _func);
		/* Release data field. */
		if (_func) _func (_t);
		/* Release node memory. */
		free (_t);
	}
}


pbtree bt_create_pre_inorder (char* _preo, char* _ino) {
	size_t inend;
	if (! _preo || ! _ino) return NULL;

	inend = strlen (_ino);
	return _bt_create_pre_inorder (&_preo, _ino, _ino + inend - 1);
}

pbtree _bt_create_pre_inorder (
		char** _preo, 
		char* _inosta, 
		char* _inend) {
	pbtree root = NULL;
	char pre_ch = 0x00;

	/* Data field */
	pre_ch = **_preo;
	/* The root to be returned. */
	root = bt_create_node ((void*) pre_ch);

	if (root) {
		char* left_end = strchr (_inosta, pre_ch);
		char* right_sta = left_end + 1;
		int left_len = left_end - _inosta;
		int right_len = _inend - left_end;

		(*_preo) ++;

		if (left_len) {
			/* Start left child tree. */
			left_end --;
			root -> left = _bt_create_pre_inorder (_preo, _inosta, 
					left_end);
		}

		if (right_len)
			/* Start right child tree. */
			root -> right = _bt_create_pre_inorder (_preo, right_sta,
					right_sta + right_len - 1);
	}

	return root;
}


pbtree bt_create_post_inorder (char* _posto, char* _ino) {
	size_t inend;
	if (! _posto || ! _ino) return NULL;

	inend = strlen (_ino);
	return _bt_create_post_inorder (&_posto, _ino, _ino + inend - 1);
}

pbtree _bt_create_post_inorder (
		char** _posto, 
		char* _inosta, 
		char* _inend) {
	// TODO...
	return NULL;
}


bool bt_is_bst (pbtree _t, bt_cmpf _func) {
	static void* lastval;
	if (_t) {
		if (! bs_is_bst (_t -> left)) 
			return false;
		lastval = _t -> data;
		// TODO...
	}

	return false;
}

static void _bt_inordertraversal (pbtree _t, bt_visitf _func) {
	if (_t != NULL) {
		_bt_inordertraversal (_t -> left, _func);
		_func (_t);
		_bt_inordertraversal (_t -> right, _func);
	}
}

/* The default implementation for access tree node data.
 * Print the data field as a pointer. */
static void _default_visit_func (pbtnode _node) {
	if (_node)
		printf ("%p ", _node -> data);
}


