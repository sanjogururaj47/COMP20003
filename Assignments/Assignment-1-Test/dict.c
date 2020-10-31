/** *******************************************************
 * Program read data from a csv file, and 
 * Implement a linked list for storage and search.
 *      
 * Code written for Assignment 1 COMP20003, S2 2020.
 *      By Sanjog Gururaj, Student ID - 1099103
 * 
 * Algorithms and Data Structures are both fun!
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/* custom header files */
#include "list.h"
#include "read.h"

/** *******************************************************/

#define TRUE 1
#define FALSE 0
#define COMPLETE 0
#define KEY_LENGTH 129
#define CSV_BUF 513

/** *******************************************************/

int main(int argc, char **argv) {

    /* create an empty linked list */
    dict_t *dict = make_empty_dict();

    /* pointers to store the key and value of each line of the csv file */
    char *key, *value;
    key = (char *)malloc(KEY_LENGTH*(sizeof(char)));
    assert(key != NULL);
    value = (char *)malloc(CSV_BUF*(sizeof(char)));
    assert(value != NULL);

    /* pointers to store the key and value of the first line of csv file */
    char *columns, *key_column;
    columns = (char *)malloc(CSV_BUF*(sizeof(char)));
    assert(columns != NULL);
    key_column = (char *)malloc(KEY_LENGTH*(sizeof(char)));
    assert(key_column != NULL);
    
    /* create file pointers for reading and writing */
    FILE* fp_in = fopen(argv[1], "r");
    FILE* fp_out = fopen(argv[2], "w");


    /* check if file open failed */
    if(!fp_in) {
        printf("Failed to open input file\n");
        exit(EXIT_FAILURE);
    }
    if(!fp_out) printf("Failed to open output file\n");

    /* read the column headers */
    if(!(read_first_row(key_column, columns, fp_in))) printf("\nReached the end of file prematurely!");

    /* read and insert every line of the csv file */
    while(read_csv(key, value, columns, fp_in)) {

        /* pointers to store the key and value */
        char *insert_key, *insert_value;
        insert_key = (char *)malloc((strlen(key)+1)*(sizeof(char)));
        insert_value = (char *)malloc((strlen(value)+1)*(sizeof(char)));

        /* copy into a new location */
        strcpy(insert_key, key);
        strcpy(insert_value, value);

        /* insert into the linked list */
        if(strlen(insert_key) > 1) dict = dict_insert(dict, insert_key, insert_value);
    }

    /* insert the last key-value pairs */
    dict = dict_insert(dict, key, value);

    /* read keys from standard input and search in list */
    read_key(dict, columns, fp_out);

    /* close the file pointers */
    fclose(fp_in);
    fclose(fp_out);

    /* free the linked list */
    free_dict(dict);

    /* free the last two pointers */
    free(key_column);
    free(columns);

    /* success! */
    return COMPLETE;
}