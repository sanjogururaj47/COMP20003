/* main.c:   for ass1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "llist.h"
#include "utils.h"

int main(int argc, char *argv[]) {
	data_t *d;
	char *s=NULL;

	assert(argc>2);
	FILE *f= my_fopen(argv[1], "r");
	data_get_header(f);  // get header line of data

	// Build dict as a linked list
    list_t ll= createList();
	while ( (d= get_next_data(f)) ) {
        // print_data(d,stdout);
        ll= insert(d, ll);
	}		
	fclose(f);

	// Search for key from file atgv[2]
	f= my_fopen(argv[2],"w");
    while ( (s= getfield(stdin,NL)) ) {
        search(s, ll, f);
		free(s);
    }

	fclose(f);    
    free_list(ll);
    data_free_header();
	return 0;
}
	

