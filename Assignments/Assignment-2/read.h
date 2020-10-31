#ifndef READ_H_INCLUDED
#define READ_H_INCLUDED

#include "KDTree.h"

/* function to read a csv file and assign key */
int read_csv(char *x_key, char *y_key, char *value, char *column, FILE *fp_in);

void read_key(tree_t *root, tree_t *closest_node, char *data_headers, FILE *fp_out);

/* function to scan the keys from standard input */
void read_key_radius(tree_t *root, char *columns, FILE *fp_out);

/* function to read the column headers of a csv file */
int read_first_row(char *x_key, char *y_key, char *columns, FILE *fp_in);

#endif