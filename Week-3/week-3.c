/* calloc:
 * 	malloc for arrays calloc(size_t nobj, size_t size), also used for a set of integers
 *	also puts 0s in each locations of the array
 *
 * realloc(void *p, size_t size);
 * 	but when we use realloc we should initialize it to NULL.
 * all in stdlib.h
 *
 *
 * LINKED LISTS:
 * 	
 * 	Takes up more space than an array
 * 		since we need to store the pointers
 * 	takes extra time to allocate space for each item 
 */

/* traversal of a linked list */

void traverse(list_t *list) {
	node = list->head;
	if(node != NULL) {
		while(node->next != NULL) {
			printf("%d\n", node->data);
			node = node->next;
		}

		//print out the last nodes data
		printf("%d\n", node->key);
	}
}



/* HEADER FILES
 * 	#include "list.h", the quotes are used since it tells the compiler to search for 
 * 	the file in the cwd
 * 	use #ifndef listh (if not defined) then #define listh
 *
 * 	to compile multiple files
 * 		gcc -o dict dict.c list.c
 *
 * 		the problem with this statement is that it compiles everything from ground up
 *
 * 		that why we use:
 * MAKEFILES
 * 	
 * 	using this we can just do "make dict"
 *
 * 	for example if we have the files dict.c and list.c
 * 	we can compile them both using
 *
 * 	dict: dict.o list.o
 * 		gcc -o dict dict.o list.o
 * 	list.o: list.c list.h
 * 		gcc -c -Wall list.c
 * 	dict.o: dict.c dict.h
 * 		gcc -c -Wall dict.c
 *
 *
 * 	makefile syntax:
 *
 * 	<target>: <dependencies>
 * 		<command to run (instructions)>
 *
 * 	the .o files are just object files (text converted to binary)
 *
 *
 * 	the -Wall is to give warnings in our code
 */
