/** *******************************************************
 * 
 * includes the function definitions for reading a csv file
 * 
 */



#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>

#include "KDTree.h"
#include "read.h"

/** *******************************************************/

#define KEY_LENGTH 129
#define TRUE 1
#define FALSE 0
#define INITIAL_DEPTH 0

/** *******************************************************/

/* function to read the keys from stdin */
void read_key(tree_t *root, tree_t *closest_node, char *data_headers, FILE *fp_out) {

    int *comparisons;
    comparisons = (int *)malloc(1*sizeof(int));

    /* allocate memory for the new keys */
    double *search_x_key, *search_y_key;
    search_x_key = (double *)malloc(1*sizeof(double));
    assert(search_x_key != NULL);
    search_y_key = (double *)malloc(1*sizeof(double));
    assert(search_y_key != NULL);

    while(scanf("%lf %lf", search_x_key, search_y_key) != EOF) {

        /* compute and assign the initial distance */
        double dist = sqrt(pow(*search_x_key - *(root->x_key),2) 
                + pow(*search_y_key - *(root->y_key),2));

        /* retrieve the closest node */
        closest_node = search_tree(root, search_x_key, search_y_key, 
                                    INITIAL_DEPTH, &dist, closest_node, comparisons);

        if(closest_node != NULL) {
            
            /* check if current node is a linked list and print the values */
            if(closest_node->l_list->next != NULL) traverse_linked_list(
               closest_node, data_headers, search_x_key, search_y_key, fp_out);

            else print_result(closest_node, data_headers, search_x_key,
                 search_y_key, fp_out);
        }
        printf("%.6lf %.6lf --> %d\n", *search_x_key, *search_y_key, *comparisons); 
    }
    free(search_x_key);
    free(search_y_key);
    free(comparisons);
}

/* function to read keys from stdin */
void read_key_radius(tree_t *root, char *columns, FILE *fp_out) {

    int *comparisons;
    comparisons = (int *)malloc(1*sizeof(int));

    /* allocate memory for the new keys and radius */
    double *search_x_key, *search_y_key, *radius;
    search_x_key = (double *)malloc(1*sizeof(double));
    assert(search_x_key != NULL);
    search_y_key = (double *)malloc(1*sizeof(double));
    assert(search_y_key != NULL);
    radius = (double *)malloc(1*sizeof(double));
    assert(radius != NULL);


    while(scanf("%lf %lf %lf", search_x_key, search_y_key, radius) != EOF) {

        int found = 0, result = 0;
        result = search_tree_radius(root, search_x_key, search_y_key, 
                    INITIAL_DEPTH, radius, &found, columns, fp_out, comparisons);

        if(result == 0) {
            fprintf(fp_out, "%.6lf %.6lf %.4f --> %s\n", *search_x_key, *search_y_key,
                 *radius, "NOT FOUND");
            //printf("%.6lf %.6lf %.4f --> %s\n", *search_x_key, *search_y_key,
              //   *radius, "NOT FOUND");
        }
        printf("%.6lf %.6lf %.4f--> %d\n", *search_x_key, *search_y_key, *radius, *comparisons); 
    }
    free(search_x_key);
    free(search_y_key);
    free(comparisons);
    free(radius);
}

/* function to scan the keys from standard input */
int read_first_row(char *x_key, char *y_key, char *columns, FILE *fp_in) {

    char c;
    int num_commas = 0;
    int i = 0, j = 0;

    /* read a line of the csv file */
    while((c = fgetc(fp_in)) && c != '\n' && c != EOF && c != '\r') {

        /* arrived at the x-coordinate */
        if(num_commas == 8) {
            j = 0;
            columns[i++] = x_key[j++] = c;

            /* copy column name into key */
            while((c = fgetc(fp_in)) && c != ',') columns[i++] = x_key[j++] = c;
            if(c == ',') columns[i++] = ',';

            num_commas++;
            continue;
        }

        /* arrived at the y-coordinate */
        if(num_commas == 9) {
            j = 0;
            columns[i++] = y_key[j++] = c;

            /* copy column name into key */
            while((c = fgetc(fp_in)) && c != ',') columns[i++] = y_key[j++] = c;
            if(c == ',') columns[i++] = ',';

            num_commas++;
            continue;
        }

        if(c == ',') num_commas++;

        columns[i++] = c;
    }

    /* terminate the strings */
    columns[i] = '\0';
    x_key[j] = '\0';
    y_key[j] = '\0';

    if(c == EOF) return FALSE;

    return TRUE;

}

/* function to read the column headers of a csv file */
int read_csv(char *x_key, char *y_key, char *value, char *column, FILE *fp_in) {

    char c;
    int num_commas = 0;

    int i = 0, j= 0, k = 0;

    /* read a line of the csv file */
    while((c = fgetc(fp_in)) && c != '\n' && c != EOF && c != '\r') {

        /* arrived at the key column */
        if(num_commas == 8) {
            j = 0;

            if(c == ',') value[i++] = '~';

            value[i++] = x_key[j++] = c;

            /* copy column name into key */
            while((c = fgetc(fp_in)) && c != ',') value[i++] = x_key[j++] = c;
            if (c == ',') value[i++] = '~';
            
            num_commas++;
            continue;
        }

        else if(num_commas == 9) {
            k = 0;

            if(c == ',') value[i++] = '~';
            value[i++] = y_key[k++] = c;

            /* copy column name into key */
            while((c = fgetc(fp_in)) && c != ',') value[i++] = y_key[k++] = c;
            if(c == ',') value[i++] = '~';
            
            num_commas++;
            continue; 
        }
        else {
            if(c == '"') {

                /* copy until end of second quote */
                while((c = fgetc(fp_in)) && c != '"') value[i++] = c;
                continue;
            }

            if(c == ',') {

                /* replace comma with tilde */
                value[i++] = '~';
                num_commas++;
                continue;
            }

            value[i++] = c;
        }
    }

    /* terminate the strings */
    value[i] = '\0';
    x_key[j] = '\0';
    y_key[k] = '\0';

    if(c == EOF) return FALSE;

    return TRUE;
}