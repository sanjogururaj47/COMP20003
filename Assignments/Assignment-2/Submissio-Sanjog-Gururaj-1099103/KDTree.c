/** *******************************************************
 * 
 * Inlcudes the function definition for the K-D tree data structures operations
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<math.h>
#include<float.h>

#include "KDTree.h"

/** *******************************************************/

#define TRUE 1
#define FALSE 0


/* function to create a new node for a tree */
tree_t* new_node(double *x, double *y, data_t *data) {

    tree_t *new_node = (tree_t *)malloc(1*sizeof(tree_t));
    assert(new_node != NULL);
    
    /* insert into the linked list and assign new head */
    new_node->l_list = insert_linked_list(data, data->value);
    new_node->x_key = x;
    new_node->y_key = y;

    new_node->left = new_node->right = NULL;

    return new_node;
}

/* function to insert a node into a singly linked list */
data_t* insert_linked_list(data_t *list, char *value) {

    data_t *new_node = (data_t *)malloc(1*sizeof(data_t));
    assert(new_node != NULL);
    new_node->value = value;
    new_node->next = list;
    return new_node;
}

/* function to traverse a linked list and print the results */
void traverse_linked_list(tree_t *root, char *data_headers, double *search_x_key, double *search_y_key, FILE *fp_out) {

    tree_t *temp = root;
    while(temp->l_list->next != NULL) {
        print_result(temp, data_headers, search_x_key, search_y_key, fp_out);
        temp->l_list = temp->l_list->next;
    }
}

/* function to check for collision */
int same_node(tree_t *root, double *x, double *y) {

    if((fabs(*(root->x_key) - *x) < DBL_EPSILON) && (fabs(*(root->y_key) - *y) < DBL_EPSILON)) {
        return TRUE;
    }
    return FALSE;
}

/* function to recursively insert into the tree */
tree_t* tree_insert(tree_t *root, double *x, double *y, data_t *data, unsigned depth) {

    if (root == NULL) return new_node(x, y, data);

    if(same_node(root, x, y)) {
        root->l_list = insert_linked_list(root->l_list, data->value);
        return root;
    }

    /* check the depth of the tree */
    if(depth%2 == 0) {
        if(*x < *(root->x_key)) {
            root->left = tree_insert(root->left, x, y, data, depth + 1);            
        }
        else if(*x >= *(root->x_key)) {
            root->right = tree_insert(root->right, x, y, data, depth + 1);            
        }
    }
    
    else {
        if(*y < *(root->y_key)) { 
            root->left = tree_insert(root->left, x, y, data, depth + 1);
            
        }
        else if(*y >= *(root->y_key)) {
            root->right = tree_insert(root->right, x, y, data, depth + 1); 
        }
    }

    return root;
}

/* function to find the closest node for given coordinates */
tree_t* search_tree(tree_t *root, double *x, double *y, unsigned depth, double *dist, tree_t *closest_node, int *comparisons) {

    /* find the number of comparisons every time we recurse */
    (*comparisons)++;

    if(root == NULL) return closest_node;

    /* check for equality */
    if((fabs(*(root->x_key) - *x) < DBL_EPSILON) && (fabs(*(root->y_key) - *y) < DBL_EPSILON)) {
        closest_node = root;
        return closest_node;
    }

    double x_diff = fabs(*(root->x_key) - *x);
    double y_diff = fabs(*(root->y_key) - *y);
    double curr_dist = sqrt(pow(x_diff,2) + pow(y_diff,2));

    /* update the closest distance */
    if(curr_dist <= *dist) {
        *dist = curr_dist;
        closest_node = root;
    }
    
    /* recurse by comparing x or y coordinates depending on the depth */
    if(depth%2 == 0) {
        if(x_diff <= *dist) {
            closest_node = search_tree(root->left, x, y, depth + 1, dist, closest_node, comparisons);
            closest_node = search_tree(root->right, x, y, depth + 1, dist, closest_node, comparisons);  
        }
        else if(*x < *(root->x_key)) {
            closest_node = search_tree(root->left, x, y, depth + 1, dist, closest_node, comparisons);
                
            }
        else if(*x >= *(root->x_key)) {
            closest_node = search_tree(root->right, x, y, depth + 1, dist, closest_node, comparisons);
            
        }
    }
    
    else {
        if(y_diff <= *dist) {
            closest_node = search_tree(root->left, x, y, depth + 1, dist, closest_node, comparisons);
            closest_node = search_tree(root->right, x, y, depth + 1, dist, closest_node, comparisons);  
        }
        else if(*y < *(root->y_key)) { 
            closest_node = search_tree(root->left, x, y, depth + 1, dist, closest_node, comparisons); 
        }
        else if(*y >= *(root->y_key)) {
            closest_node = search_tree(root->right, x, y, depth + 1, dist, closest_node, comparisons);  
            
        }
    }
    return closest_node;
}

/* function to find all nodes within a given radius of the coordinates */
int search_tree_radius(tree_t *root, double *x, double *y, unsigned depth, double *radius, int *found, char* columns, FILE *fp_out, int *comparisons) {

    /* find the number of comparisons every time we recurse */
    (*comparisons)++;

    if(root == NULL) {
        return *found;
    }

    /* compute the distance between current node and search coordinates */
    double x_diff = fabs(*(root->x_key) - *x);
    double y_diff = fabs(*(root->y_key) - *y);
    double curr_dist = sqrt(pow(x_diff,2) + pow(y_diff,2));

    /* print if within the radius */
    if(curr_dist <= *radius) {

        (*found)++;
        tree_t *temp = root;

        /* traverse and print if multiple values present */
        while(temp->l_list->next != NULL) {
            print_radius_result(temp, x, y, radius, columns, fp_out);
            temp->l_list = temp->l_list->next;
        }
   }

    /* recurse by comparing x or y coordinates depending on the depth */
    if(depth%2 == 0) {

        if(curr_dist <= *radius) {
            search_tree_radius(root->left, x, y, depth + 1, radius, found, columns, fp_out, comparisons);
            search_tree_radius(root->right, x, y, depth + 1, radius, found, columns, fp_out, comparisons);
        }

        else if(*x < *(root->x_key)) {
            search_tree_radius(root->left, x, y, depth + 1, radius, found, columns, fp_out, comparisons);
        }
        else if(*x >= *(root->x_key)) {
            search_tree_radius(root->right, x, y, depth + 1, radius, found, columns, fp_out, comparisons);
            
        }
    }
    
    else if(depth%2 != 0) {

        if(curr_dist <= *radius) {
            search_tree_radius(root->left, x, y, depth + 1, radius, found, columns, fp_out, comparisons);
            search_tree_radius(root->right, x, y, depth + 1, radius, found, columns, fp_out, comparisons);
        }

        else if(*y < *(root->y_key)) { 
            search_tree_radius(root->left, x, y, depth + 1, radius, found, columns, fp_out, comparisons);
            
        }
        else if(*y > *(root->y_key)) {
            search_tree_radius(root->right, x, y, depth + 1, radius, found, columns, fp_out, comparisons);
        }
    }
    return *found;
}

/* function to print the result in a well formatted manner */
void print_result(tree_t *root, char *data_headers, double *search_x_key, double *search_y_key, FILE *fp_out) {

    /* print the key */
    //printf("%.6lf %.6lf --> ", *search_x_key, *search_y_key);
    fprintf(fp_out, "%.6lf %.6lf --> ", *search_x_key, *search_y_key);

    /* copy the first row of the csv file containing column headers */
    char column_header[strlen(data_headers)];
    char value[strlen(root->l_list->value)];

    /* pointers for strtok_r() */
    char *save_ptr1, *save_ptr2;

    strcpy(column_header, data_headers);
    strcpy(value, root->l_list->value);

    /* set delimiters for strtok_r() */
    const char col_delim[2] = ",";
    const char val_delim[2] = "~";

    /* get the first token */
    char *col_token = strtok_r(column_header, col_delim, &save_ptr1);
    char *value_token = strtok_r(value, val_delim, &save_ptr2);

    while(value_token != NULL &&  col_token != NULL) {

        /* print the tokens in the specified format */
        //printf("%s: %s || ", col_token, value_token);
        fprintf(fp_out, "%s: %s || ", col_token, value_token);

        /* get the subsequent tokens */
        col_token = strtok_r(NULL, col_delim, &save_ptr1); 
        value_token = strtok_r(NULL, val_delim, &save_ptr2); 
    }
    fprintf(fp_out, "\n");
    //printf("\n");
}

/* function to print the result in a well formatted manner */
void print_radius_result(tree_t *root, double *x, double *y, double *radius, char *columns, FILE *fp_out) {
   
    /* print the key */
    //printf("%.6lf %.6lf %.4f --> ", *x, *y, *radius);
    fprintf(fp_out, "%.6lf %.6lf %.4f--> ", *x, *y, *radius);

    /* copy the first row of the csv file containing column headers */
    char column_header[strlen(columns)];
    char value[strlen(root->l_list->value)];

    /* pointers for strtok_r() */
    char *save_ptr1, *save_ptr2;

    strcpy(column_header, columns);
    strcpy(value, root->l_list->value);

    /* set delimiters for strtok_r() */
    const char col_delim[2] = ",";
    const char val_delim[2] = "~";

    /* get the first token */
    char *col_token = strtok_r(column_header, col_delim, &save_ptr1);
    char *value_token = strtok_r(value, val_delim, &save_ptr2);

    while(value_token != NULL &&  col_token != NULL) {

        /* print the tokens in the specified format */
        //printf("%s: %s || ", col_token, value_token);
        fprintf(fp_out, "%s: %s || ", col_token, value_token);

        /* get the subsequent tokens */
        col_token = strtok_r(NULL, col_delim, &save_ptr1); 
        value_token = strtok_r(NULL, val_delim, &save_ptr2); 
    }
    fprintf(fp_out, "\n"); 
    //printf("\n");
}


void free_tree(tree_t *root) {
    
    if(root != NULL) {

        /* post order recurse */
        free_tree(root->left);
        free_tree(root->right);

        /* free the linked list in the node */
        if(root->l_list != NULL) free_list(root->l_list);
        
        root->right = root->left = NULL;

        /* free the other elements of the node */
        free(root->x_key);
        free(root->y_key);
        free(root);
    }
}

void free_list(data_t *l_list) {

	data_t *p = l_list;

	while (p->next != NULL) {

		data_t *temp= p;
		p = p->next;
		free(temp);
	}
}