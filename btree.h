/*
 * A simple binary tree defination of chained 
 * storage structure.
 *
 * Author : ez
 * Date : 2018/5/11
 *
 *  _     _                 
 * | |__ | |_ _ __ ___  ___ 
 * | '_ \| __| '__/ _ \/ _ \
 * | |_) | |_| | |  __/  __/
 * |_.__/ \__|_|  \___|\___|
 *                           
 */

#ifndef _BTREE_H_
#	define _BTREE_H_

typedef struct _btree btree, btnode, 
				*pbtree, *pbtnode;

typedef struct _btree {
	/* Pointer to exactual data block. 
	 * If your data block length is less 
	 * than the width of sizeof(void*),
	 * just keep it with explicity conversion. 
	 * E.g.:  data = (void*) 0x340f; */
	void* data;

	/* Pointer field to left, right child. */
	btnode* left, *right;
} btree, *pbtree,
	btnode, *pbtnode;


/* A function signature for visiting
 * each `btree' empty. */
typedef void (*bt_visitf) (pbtnode);


/* Create a new tree by inputing data list
 * and it's length. The list shell be supposed
 * as a preorder traversal sequency.
 * $1  The data list. 
 * $2  The length of $1. 
 * 
 * Return the new tree pointer while successful. 
 * Or NULL if $1 is NULL, empty or another unexpected
 * error (e.g. out of memory). */
extern pbtree bt_create (void**, int);


/* Create a new tree by its preorder and inorder
 * traversal sequency. If one of $1 and $2 is NULL,
 * function return NULL, and occurring error as well.
 * $1  The preorder secuency.
 * $2  The inorder sequency.
 *
 * Return the new tree pointer while successful. */
extern pbtree bt_create_pre_inorder (char*, char*);


/* Create a new tree node by inputing data.
 * $1  The data pointer. 
 * 
 * Return a new tree node while successful. 
 * Or NULL if $1 is NULL or another unexpected
 * error (e.g. out of memory). */
extern pbtnode bt_create_node (void*);

/* Preordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
extern void bt_pretraversal (pbtree, bt_visitf);


/* Postordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
extern void bt_posttraversal (pbtree, bt_visitf);


/* Inordering traverse each node of a tree by invoke 
 * the input function pointer $2. A default implementation 
 * will be used when caller gets a NULL function. */
extern void bt_inordertraversal (pbtree, bt_visitf);


#endif // ~ _BTREE_H_

