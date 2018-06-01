#ifndef _BSTREE_H_
#	define _BSTREE_H_

#include "btree.h"
#include <string.h>

/* We use btree structure to implement 
 * binary-search-tree. */
typedef btree  _bstree, bstree, bstnode;
typedef pbtree pbstree, pbstnode;


/* The function signature for comparation 
 * two element:
 *  a > b => -1
 *  a = b =>  0
 *  a < b =>  1
 */
typedef int (*bst_cmpf) (void*, void*);
typedef bt_freef bst_freef;
typedef bt_visitf bst_visitf;

/* Insert an element into a bstree entity. If the
 * target binary-search-tree is NULL while input
 * not, the function returns a new created one. 
 * Otherwise it returns $1.
 * $1  The target bst.
 * $2  Element data to be inserted. 
 * $3  Comparation function ptr. */
extern pbstree bst_insert (pbstree, void*, bst_cmpf);


/* Release a pbstree. It directly calls
 * bt_release() function. */
extern void bst_release (pbstree, bst_freef);


/* Preordering traverse each node of a binary-search-
 * tree by calls bt_pretraversal. */
extern void bst_pretraversal (pbstree, bst_visitf);

/* Search a special element from a separated 
 * binary-search-tree.
 * $1  The binary-search-tree
 * $2  The element pointer.
 * $3  Comparation function ptr.
 *
 * It successfully returns the node ptr while
 * getting element, or NULL. */
extern pbstnode bst_search (pbstree, void*, bst_cmpf);


/* Delete a special element whose data equals to $2.
 * $1  The binary-search-tree.
 * $2  An element, whose value equals this data 
 *   will be removed.
 * $3  The comparation function between two elements. 
 *
 * Successfully return the data domain ptr, and 
 * NULL is otherwise. */
extern void* bst_delete (pbstree, void*, bst_cmpf, bst_freef);


/* Create a binary-search-tree entity by an integer array. 
 * Return the tree while successful, or NULL. */
extern pbstree bst_create_int_array (int*, size_t);

/* Another deletion implementation. */
extern void bst_delete1 (pbstree, void*, bst_cmpf, bst_freef);


#endif // ~ _BSTREE_H_


