/*
 * A k-ary tree structure defination.
 * 
 * Author : ez
 * Date : 2018/6/4
 *
 *  |                 
 *  __|  __| _ \  _ \ 
 *  |   |    __/  __/ 
 * \__|_|  \___|\___| 
 *                      
 *
 */

#ifndef _TREE_H_
#	define _TREE_H_

// #	define MAX_ARK  0x10


/* A k-ary tree structure admits a 
 * representation as a child-sibling 
 * binary tree. 
 *
 * Each node corresponds to a node in
 * T with two pointers: one to the node's 
 * first child, and another one to its 
 * next sibling in T. They are singly-linked 
 * list. */
typedef struct _cstree {
	struct _cstnode* children, *siblings;
	void* data;
} cstree, cstnode, 
	*pcstree, pcstnode;

/* Another k-ary tree structure use an
 * node array as representation. 
 * Each node holds its data pointer and
 * an array index to its parent node. */
typedef struct _arrnode {
	void* data;
	int parent;
} arrnode, *parrnode;


typedef parrnode _arrtree {
	/* An array storing tree nodes. */
	parrnode nodes;

	/* The number of tree node. */
	int count;
	/* The index of tree root. */
	int root_idx;
} arrtree, *parrtree;


/* A function signature for visiting
 * each `btree' empty. */
typedef void (*t_visitf) (pcstnode);


/* A function signature for releasing
 * each data field on node. */
typedef void (*t_freef) (pcstnode);





#endif // ~ _TREE_H_
