/** BINARY SEARCH TREES 
 * 
 * A binary search tree is complete if every level, except maybe the last level is 
 * complete, and all the nodes are as far left as possible.
 *
 *
 * Depth of the tree with n nodes = log2(n)
 *
 * typical structure:
 * 	struct BST {
 * 		data_t data;
 * 		node_t *left;
 * 		node_t *right;
 * 		node_t *parent;
 * 	}
 *
 * Time complexity of BST:
 * 	
 * 	Balanced tree (best case):
 * 		height of a tree = log2(n)
 * 		path from root to any node:
 * 			longest: log2(n)
 * 			Average: log2(n)
 *
 * 	Stick (worst case):
 * 		height of a tree = n
 * 		path from root to any node
 * 			longest: n
 * 			average: n/2 
 *
 *
 *
 * Deleting an item from BST:
 * 	
 * 	In-order predecessor:
 * 		it is the right most node of the left subtree of the parent.
 * 	In-order sucessor:
 * 		it is the left most node of the right subtree of the parent.
 *
 * 	Sometimes to find the above nodes the tree may not be structured as we wish,
 * 	thus to find these nodes in such situations eg when there is no node to the left
 * 	of parent, we go back to the parent of the parent node.
 *
 * 	if the parent node is a leaf node then, the predecessor is its parent.
 * 	the successor is its grand-parent
 *
 * 	Now to delete we need to know the predecessor and successor, 
 * 	Three cases for deletion:
 * 		1. node is a leaf
 * 		2. node has either left or right child, not both
 * 		3. node has both, left and right children.
 *
 * 	for
 * 		1. just delete
 * 		2. delete and replace the node with its one child
 * 		3. delete and:
 * 			3.1 replace with childless child (if exists)
 * 			3.2 replace with in-order predecessor or successor
 *
 *
 *
 * 	Time complexity for deletion is also log(n)
 *
 *
 * Traversal:
 * 	in-order traversal: we first go to the left most node and then visit the node 
 * 		if there are no further left nodes, once visited we go back to the 
 * 		parent node and visit it, then we visit the right node and check if there
 * 		is a left node, if not we visit and check for a right node.
 *
 * 		thus the order of traversal results in an ascending order of keys.
 *
 * 		LVR
 *
 * 	Pre-order traversal:
 * 		Current node and recurse on the left and right nodes, used for insertion, comes out as the
 *		exact order of the tree.
 *               
 * 	        VLR        
 *
 * 	Post-order traversal:
 * 		recurse on the left and right nodes and then do somn on the current node, can be used to 
 * 		free the entire tree, so we delete the child and then the parent.
 *		
 * 		LRV	
 */


/** 
 * BALANCED TREES:
 * 	Methods to ensure that BST is perfectly balanced:
 * 	
 * 	we try to keep the height of the tree to be log2(n)
 *
 * 	AVL Trees (Adelson-Velskii and Landis)
 * 	
 * 	- pros:
 * 		- height is always < 1.44*log2(n)
 * 		- always balanced tree (nearly)
 * 		- complexity is always O(logn)
 * 	- cons:
 * 		- very fiddly to code, must keep track of:
 * 			- insertion path
 * 			- height of all subtrees
 * 		- balancing adds time to insertion (but constant time)
 *
 *
 * 	- Details
 * 		- we keep track of the height of subtrees of every node
 * 			- balance node every time difference between subtree heights is > 1
 * 			- this balancing operation is called AVL rotation
 *
 * 		- There are two categories of unbalances trees
 * 			- outside unbalanced (LL and RR): the subtree on the outside is greater than inside 
 * 				(left or right).
 * 			- inside unbalanced (RL and LR): the subtree on the inside is greater than the one on
 * 				the outside eg. the left subtree of a right child.
 *
 * 		- How to balance:
 * 			- Outside imbalance:
 * 				- rotate to rebalance
 * 			- Inside imbalance:
 * 				- two rotations
 */



#include<stdio.h>

/* balancing an outside imbalance with one rotation */

void rotate_right(node) {
	
	//Auxilary variables
	left = node.left;
	left_right = left.right;
	parent = node.parent;

	//operations
	left.parent = parent;
	left.right = node;
	node.left = left_right;
	node.parent = left;
}

void rotate_left(node) {

	//auxilary variables
	right = node.right;
	right_left = right.left;
	parent - node.parent;

	//operations
	right.parent = parent;
	right.left = node;
	node.right = right_left;
	node.parent = right;
}


/* balancing an inside imbalance */

/* for the first case the first rotation creates an outside imbalance
 * which then can be balanced with one rotation
 */

/* right left double rotation  or left right double rotation */



/* AVL INSERTION */

node* insert(node *tree, node *new_node) {
	if(tree == NULL) {
		tree = new_node;
	}
	else if (new_node->key < tree->key) {
		tree->left = insert(tree->left, new_node);
		rotate_left(new_node);
	}
	else {
		tree->right = insert(tree->right, new_node);
		rotate_right(new_node);
	}
	return tree;
}
