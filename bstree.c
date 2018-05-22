#include "bstree.h"
#include "common.h"
#include <stdlib.h>


static int _default_cmp_func (void*, void*);


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

pbstnode bst_search (pbstree _t, void* _e) {
	return NULL;
}


static int _default_cmp_func (void* _a, void* _b) {
	if (_a == _b) return CMP_EQ;
	return _a < _b ? CMP_LT : CMP_GT;
}

