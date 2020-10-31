/** *******************************************************
 * Program read data from a csv file, and 
 * Implement a KD-Tree for storage and search
 *      
 * Code written for Assignment 2 COMP20003, S2 2020.
 *      By Sanjog Gururaj, Student ID - 1099103
 * 
 * Algorithms and Data Structures are both fun!
 */


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include<assert.h>
#include<math.h>
#include <float.h>

/* custom header files */
#include "read.h"
#include "KDTree.h"

/** *******************************************************/

#define TRUE 1
#define FALSE 0
#define COMPLETE 0
#define KEY_LENGTH 129
#define CSV_BUF 513
#define INITIAL_DEPTH 0

/** *******************************************************/

/** *******************************************************/

int main(int argc, char **argv) {

    tree_t *root = NULL;
    
    /* pointers to store the headers of the data */
    char *x_key_header, *y_key_header, *data_headers;

    x_key_header = (char *)malloc(KEY_LENGTH*(sizeof(char)));
    assert(x_key_header != NULL);
    y_key_header = (char *)malloc(KEY_LENGTH*(sizeof(char)));
    assert(y_key_header != NULL);
    data_headers = (char *)malloc(CSV_BUF*(sizeof(char)));
    assert(data_headers != NULL);

    /* create file pointers for reading and writing */
    FILE* fp_in = fopen(argv[1], "r");
    FILE* fp_out = fopen(argv[2], "w");

    /* check if file open failed */
    if(!fp_in) {
        printf("Failed to open input file\n");
        exit(EXIT_FAILURE);
    }
    if(!fp_out) printf("Failed to open output file\n");

    if(!read_first_row(x_key_header, y_key_header, data_headers, fp_in)) printf("reached end of file prematurely!\n");

    /* pointers to store the key and value of each line of the csv file */
    char *x_key, *y_key, *value;
    x_key = (char *)malloc(KEY_LENGTH*(sizeof(char)));
    assert(x_key != NULL);
    y_key = (char *)malloc(KEY_LENGTH*(sizeof(char)));
    assert(y_key != NULL);
    value = (char *)malloc(CSV_BUF*(sizeof(char)));
    assert(value != NULL);

    /* read and insert every line of the csv file */
    while(read_csv(x_key, y_key, value, data_headers, fp_in)) {
        /* pointers to store the key */
        double *insert_x_key, *insert_y_key;
        insert_x_key = (double *)malloc(1*sizeof(double));
        assert(insert_x_key != NULL);
        insert_y_key = (double *)malloc(1*sizeof(double));
        assert(insert_y_key != NULL);

        char *ref1, *ref2;
        *insert_x_key = strtod(x_key, &ref1);
        *insert_y_key = strtod(y_key, &ref2);

        data_t *data;
        data = (data_t *)malloc(1*(sizeof(data_t))); 
        assert(data != NULL);
        data->value = (char *)malloc((strlen(value)+1)*(sizeof(char)));
        assert(data->value != NULL);

        data->next = NULL;

        /* copy data into a new location */
        strcpy(data->value, value);

        if(fabs(*insert_y_key + *insert_x_key) > DBL_EPSILON) {
            if (strlen(data->value) > 1) root = tree_insert(root, insert_x_key,
                                    insert_y_key, data, INITIAL_DEPTH);
        }
    }

    /* insert the last node */
    double *insert_x_key, *insert_y_key;
    insert_x_key = (double *)malloc(1*sizeof(double));
    assert(insert_x_key != NULL);
    insert_y_key = (double *)malloc(1*sizeof(double));
    assert(insert_y_key != NULL);

    char *ref1, *ref2;
    *insert_x_key = strtod(x_key, &ref1);
    *insert_y_key = strtod(y_key, &ref2);

    /* create a new data node */
    data_t *data;
    data = (data_t *)malloc(1*(sizeof(data_t))); 
    assert(data != NULL);
    data->value = (char *)malloc((strlen(value)+1)*(sizeof(char)));
    assert(data->value != NULL);

    data->next = NULL;

    strcpy(data->value, value);

    if(fabs(*insert_x_key + *insert_y_key) > DBL_EPSILON) {
        if (strlen(data->value) > 1) root = tree_insert(root, insert_x_key,
                                 insert_y_key, data, INITIAL_DEPTH);
    }
     
    
    tree_t *closest_node = root;
    read_key(root, closest_node, data_headers, fp_out);

    /* free the KDTree */
    free_tree(root);

    /* free the remaining pointers */
    free(data->value);
    data->next = NULL;
    free(data);
    free(insert_x_key);
    free(insert_y_key);
    free(x_key_header);
    free(y_key_header);
    free(data_headers);

    fclose(fp_in);
    fclose(fp_out);

    return COMPLETE;
}


/** *******************************************************/