/** *******************************************************
 * Implement a dictionary for storage and search
 *      (Assignment 1 COMP20003, S2 2020)
 * 
 * Code written by Sanjog Gururaj, Student ID - 1099103
 * 
 * 
 */

#include <stdlib.h>
#include <stdio.h>

#include "list.h"


/** *******************************************************/

#define TRUE 1
#define FALSE 0
#define KEY_LENGTH 50
#define CSV_BUF 512

/** *******************************************************/

/* Function Prototypes */



int main(int argc, char **argv) {

    dict_t *dict = make_empty_dict();

    char key[KEY_LENGTH], value[CSV_BUF];
    char columns[CSV_BUF], key_column[KEY_LENGTH];
    
    FILE* f_pointer = fopen("small.csv", "r");
    
    /* check if file open failed */
    if(!f_pointer) printf("Cant open file\n");

    /* read the column headers */
    read_csv(key_column, columns, f_pointer);
    printf("%s\n%s\n\n\n\n", key_column, columns);

    while(read_csv(key, value, f_pointer)) {
        printf("%s\n%s\n", key, value);
        //dict_insert(dict, key, value);
    }
    /* insert the last key, value pairs */
    printf("%s\n%s\n", key, value);
    
    fclose(f_pointer);
    return 0;
}

/*void readKey(dict_t *dict) {
    char *key = NULL;
    while(scanf("%s[^\n]", key)) {
        //dict_search(dict, key);
    }
}*/

int read_csv(char *key, char *value, FILE *f_pointer) {

    char c;
    int commas = 0;


    int i = 0, j= 0;

    const char delim[2] = ",";
    //char *token = strtok(column, delim);

    //for(i = 0; i < strlen(token); i++) value[i] = token[i];
    value[i++] = ':';
    value[i++] = ' ';

    while((c = fgetc(f_pointer)) && c != '\n' && c != EOF) {

        if(commas == 5) {
            j = 0;
            key[j++] = c;
            while((c = fgetc(f_pointer)) && c != ',') {
                key[j++] = c;
            }
            commas++;
            continue;
        }

        if(c == ',') {
            commas++;
            value[i] = ' ';
            value[++i] = '|';
            value[++i] = '|';
            value[++i] = ' ';
            //token = strtok(NULL, delim);

            //for(i = 0; i < strlen(token); i++) value[i] = token[i];

            value[i++] = ':';
            value[i++] = ' '; 
        }

        value[i++] = c;
    }
    value[i] = '\0';
    key[j] = '\0';
    //printf("inside read_csv key: %s\nvalue: %s", key, value);

    if(c == EOF) return 0;

    return 1;
}




/*int main(){
dict_t *dict1 = make_empty_dict();
FILE* stream = fopen("business.csv", "r");
char line[2000];
int count = 0;
int row_count = 0;
int field_count = 0;
int fcount = 0;
while (fgets(line, 2000, stream))
{
    char* tmp = strdup(line);
    //printf("Field is %s\n", getfield(tmp, 1));
    // NOTE strtok clobbers tmp
    fcount = 0;
    count = count+1;
    char * token = strtok(tmp, ",");
    // loop through the string to extract all other tokens
    while( token != NULL ) {
      fcount = fcount + 1;
      if(fcount==6){
          insert_at_foot(dict1,token,token);
      }
        //printing each token
        token = strtok(NULL, ",");
    }
    free(tmp); 
} 
printf("%d\n",count);
printf("%s\n",dict1->foot->value);

free_dict(dict1);

 


if(c == ',') {
    commas++;
    value[i] = ' ';
    value[++i] = '|';
    value[++i] = '|';
    value[++i] = ' ';
    continue;
}

}*/




/* alright frick.c mate
/** *******************************************************
 * Implement a dictionary for storage and search
 *      (Assignment 1 COMP20003, S2 2020)
 * 
 * Code written by Sanjog Gururaj, Student ID - 1099103
 * 
 * 
 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "list.h"
#include "read.h"


/*  *******************************************************/

/*#define TRUE 1
#define FALSE 0
#define KEY_LENGTH 50
#define CSV_BUF 512 */

/** *******************************************************/

/* typedef struct node node_t;

struct node {
    char *key, *value;
    node_t* next;
};

typedef struct {
    node_t *head, *foot;
}dict_t; */

/** *******************************************************/

/* Function Prototypes */

/* dict_t *make_empty_dict(void);
dict_t *dict_insert(dict_t *dict, char *key, char *value);
void dict_search(dict_t *dict, char *key, char *columns, FILE *fp_out);
void traverse_dict(dict_t *dict); */
/* int read_csv(char *key, char *value, char *column, FILE *fp_in);
void readKey(dict_t *dict, char *columns, FILE *fp_out);
int read_first_row(char *key, char *columns, FILE *fp_in); */
/* void print_result(char *key, char *val, char *columns, FILE *fp_out); */


/* int main(int argc, char **argv) {

    dict_t *dict = make_empty_dict();

    char *key, *value;
    key = (char *)malloc(KEY_LENGTH*(sizeof(char)));
    assert(key != NULL);
    value = (char *)malloc(CSV_BUF*(sizeof(char)));
    assert(value != NULL);

    char *columns, *key_column;
    columns = (char *)malloc(CSV_BUF*(sizeof(char)));
    assert(columns != NULL);
    key_column = (char *)malloc(KEY_LENGTH*(sizeof(char)));
    assert(key_column != NULL);
    
    //FILE* fp_in = fopen("Business_establishment_trading_name_and_industry_classification_2018.csv", "r");
    FILE* fp_in = fopen(argv[1], "r");
    FILE* fp_out = fopen(argv[2], "w");
    //FILE* fp_in = fopen("small.csv", "r");
    /* check if file open failed 
    if(!fp_in) printf("Cant open file\n");

    /* read the column headers 
    if(!(read_first_row(key_column, columns, fp_in))) printf("\nthis one uh Reached the end of file prematurely!");
    //printf("\n\nKey: %s\nColumn headers: %s", key_column, columns);

    while(read_csv(key, value, columns, fp_in)) {
        char *insert_key, *insert_value;
        insert_key = (char *)malloc(strlen(key));
        insert_value = (char *)malloc(strlen(value));

        strcpy(insert_key, key);
        strcpy(insert_value, value);

        if(strlen(insert_key) > 1) dict = dict_insert(dict, insert_key, insert_value);
    }

    /* insert the last key, value pairs 
    dict = dict_insert(dict, key, value);

    //traverse_dict(dict);
    readKey(dict, columns, fp_out);

    fclose(fp_in);
    fclose(fp_out);

    /* free key and columm here i think? 


    return 0;
} */

/* void readKey(dict_t *dict, char *columns, FILE *fp_out) {
    char key[100];

    while(fgets(key, 100, stdin)) dict_search(dict, key, columns, fp_out);
}

int read_first_row(char *key, char *columns, FILE *fp_in) {
    printf("\nReached the end of file prematurely!");
    char c;
    int num_commas = 0;
    int i = 0, j = 0;

    while((c = fgetc(fp_in)) && c != '\n' && c != EOF && c != '\r') {

        if(num_commas == 5) {
            j = 0;
            key[j++] = c;
            while((c = fgetc(fp_in)) && c != ',') {
                key[j++] = c;
            }
            num_commas++;
            continue;
        }

        if(c == ',') num_commas++;

        columns[i++] = c;
    }
    columns[i] = '\0';
    key[j] = '\0';

    //printf("\n\n\n%s", key);

    printf("\nReached the end of file prematurely!");
    if(c == EOF) return 0;
    printf("\nReached the end of file prematurely!");

    return 1;

}

int read_csv(char *key, char *value, char *column, FILE *fp_in) {

    char c;
    int num_commas = 0;

    //printf("\n\n\nthe fucking column mate %s", column);

    int i = 0, j= 0;

    while((c = fgetc(fp_in)) && c != '\n' && c != EOF && c != '\r') {

        if(num_commas == 5) {
            j = 0;
            if(c == '"') {
                while((c = fgetc(fp_in))) {
                    if(c == '"') {
                        if((c = fgetc(fp_in)) == ','){
                            num_commas++;
                            break;
                        }
                    }
                    key[j++] = c;
                }
                continue;
            }

            key[j++] = c;
            while((c = fgetc(fp_in)) && c != ',') {
                key[j++] = c;
            }
            num_commas++;
            continue;
        //}
        }
        else{

            if(c == '"') {
                while((c = fgetc(fp_in)) && c != '"') value[i++] = c;
                continue;
            }

            /* if(c == '"') {
                while((c = fgetc(fp_in))) {
                    if(c == '"') {
                        if((c = fgetc(fp_in)) == ','){
                            num_commas++;
                            break;
                        }
                    }
                    value[i++] = c;
                }
                continue;
            }

            if(c == ',') {
                value[i++] = '~';
                num_commas++;
                continue;
            }

            value[i++] = c;
        }
    }
    value[i] = '\0';
    key[j] = '\0';

    //printf("\n\n\n%s", key);

    if(c == EOF) return 0;

    return 1;
} */


/*dict_t *make_empty_dict(void) {
    dict_t *dict = (dict_t *)malloc(1*sizeof(dict_t));
    assert(dict != NULL);
    dict->head = NULL;
    dict->foot = NULL;
    return dict;
}*/

/* 
dict_t *dict_insert(dict_t *dict, char *key, char *value) {

    node_t *new_node = (node_t *)malloc(1*sizeof(node_t));
    assert(new_node != NULL);

    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;

    if(dict->foot == NULL) dict->head = new_node;

    else dict->foot->next = new_node;

    dict->foot = new_node;

    return dict;
}

void dict_search(dict_t *dict, char *key, char *columns, FILE *fp_out) {

    int occured = 0;
    node_t *node = dict->head;
    assert(node != NULL);

    while(node) {
        if(!(strncmp(node->key, key, strlen(key) - 1))) {
            occured++;
            print_result(key, node->value, columns, fp_out);
            //printf("\n%s --> %s", key, node->value);
        }
        node = node->next;
    }

    if(!occured) {
        printf("\n%s --> NOTFOUND", key);
        fprintf(fp_out, "\n%s --> NOTFOUND", key);
        
    }
}

void print_result(char *key, char *val, char *columns, FILE *fp_out) {
    printf("\n%s--> ", key);
    fprintf(fp_out, "\n%s--> ", key);


    char column_header[strlen(columns)];
    char value[strlen(val)];
    char *save_ptr1, *save_ptr2;

    strcpy(column_header, columns);
    strcpy(value, val);


    const char col_delim[2] = ",";
    const char val_delim[2] = "~";

    char *col_token = strtok_r(column_header, col_delim, &save_ptr1);
    char *value_token = strtok_r(value, val_delim, &save_ptr2);

    while(value_token != NULL &&  col_token != NULL) {
        printf("%s: %s || ", col_token, value_token);
        fprintf(fp_out, "%s: %s || ", col_token, value_token);

        col_token = strtok_r(NULL, col_delim, &save_ptr1); 
        value_token = strtok_r(NULL, val_delim, &save_ptr2); 
    }
}

void traverse_dict(dict_t *dict) {
    node_t *node = (node_t *)malloc(1*sizeof(node_t));
    assert(node != NULL);

    node = dict->head;

    int lines = 1;

    while(node) {
        printf("\n\n%s --> %s", node->key, node->value);
        node = node->next;
        lines ++;
    }
} */