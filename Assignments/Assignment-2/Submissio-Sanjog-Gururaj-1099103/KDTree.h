#ifndef KDTREE_H_INCLUDED 
#define KDTREE_H_INCLUDED

typedef struct data data_t;
typedef struct tree tree_t;
typedef struct list list_t;

struct data {
    char *value;
    data_t *next;
};

/*struct list {
    data_t *head;
    data_t *foot;
};*/

struct tree {
    data_t *l_list;
    double *x_key, *y_key;
    tree_t *right;
    tree_t *left;
    tree_t *parent;
};

/* function to create a new tree node */
tree_t* new_node(double *x, double *y, data_t *data);

/* function to insert a node into a singly linked list */
data_t* insert_linked_list(data_t *list, char *value);

/* function to traverse a linked list and print the results */
void traverse_linked_list(tree_t *root, char *data_headers, double *search_x_key, double *search_y_key, FILE *fp_out);

/* function to check for collision */
int same_node(tree_t *root, double *x, double *y);

/* function to insert into the tree */
tree_t* tree_insert(tree_t *root, double *x, double *y, data_t *data, unsigned depth);

/* function to search the tree */
tree_t* search_tree(tree_t *root, double *x_key, double *y_key, unsigned depth, double *dist, tree_t *closest_node, int *comparisons);

/* function to find all nodes within a given radius of the coordinates */
int search_tree_radius(tree_t *root, double *x_key, double *y_key, unsigned depth, double *radius, int *found, char *columns, FILE *fp_out, int *comparisons);

/* function to print the result in a well formatted manner */
void print_result(tree_t *root, char *data_headers, double *search_x_key, double *search_y_key, FILE *fp_out);

/* function to print the result in a well formatted manner */
void print_radius_result(tree_t *root, double *x, double *y, double *radius, char *columns, FILE *fp_out);

/* function to free the tree */
void free_tree(tree_t *root);

/* function to free a linked list */
void free_list(data_t *l_list);



#endif