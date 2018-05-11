#include "btree.h"
#include <stdio.h>
#include <stdlib.h>


static void _default_visit_func (pbtnode);
static void _bt_pretraversal (pbtree, bt_visitf);
static void _bt_posttraversal (pbtree, bt_visitf);
static void _bt_inordertraversal (pbtree, bt_visitf);


/* Create a new tree by inputing data list
 * and it's length. The list shell be supposed
 * as a preorder traversal sequency.
 * $1  The data list. 
 * $2  The length of $1. 
 * 
 * Return the new tree pointer while successful. 
 * Or NULL if $1 is NULL, empty or another unexpected
 * error (e.g. out of memory). */
pbtree bt_create (void** _data, int _len) {
	// TODO...
}


/* Create a new tree node by inputing data.
 * $1  The data pointer. 
 * 
 * Return a new tree node while successful. 
 * Or NULL if $1 is NULL or another unexpected
 * error (e.g. out of memory). */
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

/* Preordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
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

/* Postordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
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

/* Inordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
void bt_inordertraversal (pbtree _t, bt_visitf _func) {
	if (! _func) _func = _default_visit_func;
	_bt_inordertraversal (_t, _func);
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


