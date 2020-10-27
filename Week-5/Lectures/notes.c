/* BINARY SEARCH TREES VARIATIONS
 *
 * 2-3-4 Trees AKA B-trees of order 4
 * 	- They have 1,2, or 3 keys and 2,3 or 4 pointers correspondingly.
 * 	- More branches per node = fewer layers of nodes
 *
 *
 * 	- Insertion:
 * 		- Items are inserted only in the leaf nodes.
 * 		- Insert upto three items per node.
 *
 * 		- If a node is full:
 * 			- the middle item is promoted to become a parent of that node.
 * 			- the node splits to accommodate the new item.
 * 		- Self balancing tree
 * 			- promotion/split method ensures that the tree always stays balanced.
 * 	- the height of a 256 pointers per node tree = log256(n)   
 *
 *
 * B+ trees:
 * 		- Usually holds a high number of pointers per node.
 * 		- Data is stored only in the leaf nodes, non-leaf only contain keys.
 * 		- Leaf nodes may include pointers to next node, to speed up sequential selection
 * 		- used to store large databases on disk.
 *
 * Red-black trees
 * 	
 * 	There are certain rules that a red-black tree must follow:
 * 		 - the root of the tree is black, the leaves of the tree is also black
 * 		 - leaves also do not contain any keys
 * 		 - a red node has to have two black children.
 * 		 - it is sort of balanced since the path from root to leaf should go through a given number 
 * 		  	of black nodes.
 * 		 - this results in the longest path being no longer than 2*(shortest path)
 * 		 - insertion involves checking the rules everytime and also re-coloring
 *
 *
 * Splay trees:
 *
 * 	A splay tree is a self-adjusting tree
 *
 * 	insertion
 * 		- insert as for BST
 * 		- "Splay" new node to the root
 *
 * 	search
 * 		- search as for BST
 * 		- "Splay" new node to root
 *
 * 	Splay = do a series of rotation that bring the node closer to the root
 * 	 - it helps spread out the nodes
 * 	 - e.g. if you have a stick, search would take O(n), but since after search we bring the result up
 * 	 	closer to the root of the tree, the successive searches would take less time.
 * 	 - it means that frequently accessed nodes are moved closer to the root.
 *
 * 2D+ trees:
 * 	- the tree are storing keys that are more than one dimensional
 *
 * 	QUAD trees:
 * 		- each node has 4 children, nodes contain information
 * 		- splits up regions with more detail
 * 		- efficient search in 2D images
 * 		- efficient way to compress images, used in video games to find the position of the player
 * 	
 * 	K-D trees:
 * 		- the root of the tree split the data on a different dimension
 * 		- efficient search in high dimension, used in machine learning (to check if a point exists in
 * 			a region).
 * 	
 *
 */



/*  DISTRIBUTION COUNTING
 *
 *  	Used to sort arrays without any comparisons
 *
 *  	Start with an array of:
 *  		- records, or
 *  		- key and pointers to records
 *  	count the number of records associated with each key value
 *
 *  	redistribute the array elements based on this count (how frequently the key appears)
 *
 *  	we get a sorted and stable sorted array
 *
 *  	stable sorted array:
 *  		- the duplicate array elements may not be sorted in their initial state
 *  			i.e. unsorted: 12, 13(1), 13(2), 11
 *  				sorted: 11, 12, 13(2), 13(1) // not stable
 *  				stable sorted: 11, 12, 13(1), 13(2) // stable
 *  		- useful when the data is sorted on one key, and within each group, sorted on another key
 *
 *  	Procedure:
 *  		- count number of records for each key
 *  		- count the cummulative count
 *  		- redistribute using an auxilary array, and increment the cummulative count for the index
 *  			as you add it to the auxilary array.
 *
 *  	time complexity:
 *  		O(n) + O(range) // range is the range of possible keys
 *  	space complexity:
 *  		O(n) + O(range)
 *
 *  	other distribution counting algorithms are LSD radix sort, MSD radix sort
 *  	although these have low time complexity, they have high space complexity.
 *  	they are also less flexible (key in high ranges).
 */


/* HASH TABLES MATE FINALLY
 *  
 *
 * Caveats:
 * 	- probablistic data structure
 * 	- most searches are O(1), but not guaranteed
 * 	- worst case is very bad
 *
 * Implementation:
 * 	- stores an array of pointers
 *	- we initialise all elements to null at first.
 *	- to insert we just point the key to the value.
 */

/* hash table */


#define RANGE 10000
#define EXAMPLEKEY 8179

struct item {
	int key;
	char *data;
}item;

void initialise(item *h_tabl[RANGE]) {
       
	for (int i = 0; i < RANGE; i++) h_table[i] = NULL;
}

void insert(item new_item) {
	new_item->key = EXAMPLEKEY;
	new_item->data = malloc(some data);
	h_tabl[EXAMPLEKEY] = new_item;
}

void search(int key) {
	return h_tabl[key]; //constant time lmao
}

/* insertion with chaining */

void insert(HT, item) {
	new_node = create_new_node();
	index = hasj(item->key);

	if(HT[index] == NULL) HT[index] = new_node;

	else {
		new_node->next = HT[index]->node;
		HT[index] = new_node;
	}
}

/* insertion with open addressing:*/

/* linear probing: 
 * 	if the spot is full, then go over to the next index and keep going until there is space to 
 * 	insert the item
 *
 * 	Average time complexity = 1/(1-a)^2
 *
 * Double Hashing:
 * 	if we come accross a collision then choose a different hash function to generate the bucket
 *
 * 	this reduces clustering in the table, with linear probring the subsequent insertions get
 * 	slower and slower
 *
 * 	double hashing is always more efficient
 *
 * 	Average time complexity = 1/(1-a) (lower than linear probing)
 *
 *
 * /


/* chaining vs open adressning */

/* Space:
 * 	chaining required extra space for the linked list nodes
 * 	open addressing needs extra space in the table
 * Time:
 * 	Similar for lightly loaded table
 * 	open addressing gets slower as alpha approaches 1
 */

/* HASHING ANALYSIS
 *
 * No efficient way to retrieve items in a sorted order
 * Good hash functions are very slow, might not be useful for small datasets
 *
 * Other uses of Hash functions
 * 	- File verification
 * 	- plagiarism detection
 * 	- encryption, we store the hash of the password instead of the password itself
 * 		so only we know the hash function and we compute the password given the hash.
 */


/* So how to implement the hash table (hash functions)
 *
 * 1. Use a circular array
 * 	squash the keys to fit in an array of limited size
 *
 * 2. use a function that maps keys evenly into this range
 *
 * 3. Have a method to handle collisions
 *
 * Hash function requirements:
 * 	- minimise collisions
 * 	- has to output a value thats within the bounds of the array
 *
 *
 *
 */























