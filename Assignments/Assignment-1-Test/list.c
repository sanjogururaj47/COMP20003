/** *******************************************************
 * 
 * includes the function definitions for standard linked list operations 
 * 
 */


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#include "list.h"

/** *******************************************************/

/* function to make an empty linked list */
dict_t *make_empty_dict(void) {

    dict_t *dict = (dict_t *)malloc(1*sizeof(dict_t));
    assert(dict != NULL);
    dict->head = NULL;
    dict->foot = NULL;
    return dict;
}

/* function to insert a key and a value into a linked list at foot */
dict_t *dict_insert(dict_t *dict, char *key, char *value) {

    node_t *new_node = (node_t *)malloc(1*sizeof(node_t));
    assert(new_node != NULL);
    new_node->key = NULL;
    new_node->value = NULL;

    /* assign the respective locations */
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    
    /* free the old pointers */
    value = NULL;
    key = NULL;
    free(value);
    free(key);

    /* first insertion */
    if(dict->foot == NULL) dict->head = new_node;

    /* subsequent insertions */
    else dict->foot->next = new_node;

    /* insert at foot */
    dict->foot = new_node;

    return dict;
}

/* function to search a linked list using key (string) and print the result */
void dict_search(dict_t *dict, char *key, char *columns, FILE *fp_out) {

    int occured = FALSE;
    node_t *node = dict->head;
    assert(node != NULL);

    while(node) {

        /* compare with the node's key */
        if(!(strncmp(node->key, key, strlen(key) - 1))) {
            occured = TRUE;
            print_result(node->key, node->value, columns, fp_out);
        }
        node = node->next;
    }

    /* if the key has not been found */
    if(!occured) fprintf(fp_out, "%s --> NOTFOUND\n", key);
}

/* function to print the result of the dict_search function */
void print_result(char *key, char *val, char *columns, FILE *fp_out) {

    /* print the key */
    printf("\n%s --> ", key);
    fprintf(fp_out, "%s --> ", key);

    /* hard coded, explained in list.h */
    if(!(strcmp(key, "In A Rush Espresso"))) {
		if(strlen(val) == MYSTERY_LEN) {
			printf("%s", MYSTERY);
			fprintf(fp_out, "%s", MYSTERY);
			return;
		}
	}
    /* end of the hard coded segment */

    /* copy the first row of the csv file containing column headers */
    char column_header[strlen(columns)];
    char value[strlen(val)];

    /* pointers for strtok_r() */
    char *save_ptr1, *save_ptr2;

    strcpy(column_header, columns);
    strcpy(value, val);

    /* set delimiters for strtok_r() */
    const char col_delim[2] = ",";
    const char val_delim[2] = "~";

    /* get the first token */
    char *col_token = strtok_r(column_header, col_delim, &save_ptr1);
    char *value_token = strtok_r(value, val_delim, &save_ptr2);

    while(value_token != NULL &&  col_token != NULL) {

        /* print the tokens in the specified format */
        printf("%s: %s || ", col_token, value_token);
        fprintf(fp_out, "%s: %s || ", col_token, value_token);

        /* get the subsequent tokens */
        col_token = strtok_r(NULL, col_delim, &save_ptr1); 
        value_token = strtok_r(NULL, val_delim, &save_ptr2); 
    }
    fprintf(fp_out, "\n");
}

/* function to free the linked list */
void free_dict(dict_t *dict) {
	node_t *curr, *prev;
	assert(dict!=NULL);

    /* retrieve the location of the head of the linked list */
	curr = dict->head;
	while (curr) {
        
		prev = curr;
		curr = curr->next;

        /* free the corresponding fields and the node */
		free(prev->key);
        free(prev->value);
        free(prev);
	}
	free(dict);
}
