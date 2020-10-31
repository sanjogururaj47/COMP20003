/*
   this is Alistair's  listops.c 
*/
#ifndef _LIST_
#define _LIST_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <string.h>

#include "data.h"

typedef struct node node_t;

struct node {
	data_t *d;
	node_t *next;
};

typedef node_t *list_t;

list_t createList(); 
list_t insert(data_t *d, list_t l);
void search(char *key, list_t l, FILE *f);
void free_list(list_t l);


#endif
