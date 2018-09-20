#include "bstree.h"
#include "common.h"
#include <stdlib.h>


static int _default_cmp_func (void*, void*);
static int _cmp_integer (void*, void*);
static pbstnode _bst_delete_node (pbstree, bst_freef);
static void _default_free_func (pbtnode _node) {}


pbstree bst_insert (pbstree _t, void* _data, bst_cmpf _func) {
	pbstree tree = _t;
	int cmp_code = -2;
	if (! _data) return NULL;

	/* Create a new tree. */
	if (! tree) {
		tree = (pbstree) bt_create_node (_data);
		return tree;
	}

	if (! _func) _func = _default_cmp_func;
	cmp_code = _func (tree -> data, _data);

	/* I've no idea yet whether it's a good 
	 * idea to ignore equal elements. */
	if (! cmp_code) return _t;
	if (cmp_code == CMP_GT)
		tree -> left = bst_insert (tree -> left, _data, _func);  // left
	else
		tree -> right = bst_insert (tree -> right, _data, _func); // right

	return tree;
}


void bst_release (pbstree _t, bst_freef _func) {
	bt_release ((pbtree) _t, (bt_freef) _func);
}

void bst_pretraversal (pbstree _t, bst_visitf _func) {
	bt_pretraversal ((pbtree) _t, (bt_visitf) _func);
}


// TODO test
void* bst_getmax (pbstree _t) {
	if (! _t) return NULL;
	while (_t) _t = _t -> right;
	return _t -> data;
}


// TODO test
void* bst_getmin (pbstree _t) {
	if (! _t) return NULL;
	while (_t) _t = _t -> left;
	return _t -> data;
}


pbstnode bst_search (pbstree _t, 
		void* _e, bst_cmpf _func) {
	pbstnode ptr = _t;
	if (! _func) _func = _default_cmp_func;

	/* Search loop. */
	while (ptr) {
		int cmp_code = _func (ptr -> data, _e);
		if (cmp_code == CMP_GT)  // To left child tree.
			ptr = ptr -> left;
		else if (cmp_code == CMP_LT) // To right child tree.
			ptr = ptr -> right;
		else return 
			ptr;
	}

	return NULL;
}


pbstree bst_create_int_array (int* _arr, size_t _num) {
	int i = 0;
	pbstree t = NULL;
	if (_num == 0 || ! _arr) return NULL;

	for (; i < _num; ++ i)
		t = bst_insert (t, (void*) (_arr [i]), _cmp_integer);
	return t;
}


pbstree bst_delete1 (pbstree _t, void* _e,
		bst_cmpf _func, bst_freef _freef) {
	/* Ensure free function isn't NULL. */
	if (_freef == NULL)
		_freef = _default_free_func;

	if (! _t) return _t;

	if (_func (_t -> data, _e) == CMP_EQ)
		/* If the _t node is the
		 * one to be deleted. */
		_t = (pbstree) _bst_delete_node (_t, _freef);
	else if (_func (_t -> data, _e) == CMP_LT)
		/* Turn right */
		_t -> right = (pbstnode) bst_delete1 (
				_t -> right, _e, _func, _freef);
	else
		/* Turn left */
		_t -> left = (pbstnode) bst_delete1 (
				_t -> left, _e, _func, _freef);
	return _t;
}


static pbstnode _bst_delete_node (pbstree node, bst_freef _freef) {
	pbstnode ret = NULL;
	if (! node -> right) {
		/* If the node has no right child 
		 * or left neither. */
		ret = node -> left;
		_freef (node -> data);
		free (node);
	} else if (! node -> left) {
		/* The node has no left child. */
		ret = node -> right;
		_freef (node -> data);
		free (node);
	} else {
		/* The node has both left and right. */
		pbstnode parent = node, 
						 replace = node -> left; // It must not be NULL.

		/* We found it's immediate predecessor.
		 * It must own left child but no right child 
		 * (certainly NULL). And its left child might 
		 * be NULL. */
		while (replace -> right)
		{
			parent = replace;
			replace = replace -> right;
		}
		node -> data = replace -> data;

		if (parent == node)
			parent -> left = replace -> left;
		else
			parent -> right = replace -> left;

		free (replace);
		_freef (node -> data);
		ret = node;
	}

	return ret;
}


static int _default_cmp_func (void* _a, void* _b) {
	if (_a == _b) return CMP_EQ;
	return _a < _b ? CMP_LT : CMP_GT;
}

static int _cmp_integer (void* _a, void* _b) {
	signed long long a = (signed long long) _a;
	signed long long b = (signed long long) _b;
	if (a == b) return CMP_EQ;
	return a > b ? CMP_GT : CMP_LT;
}

