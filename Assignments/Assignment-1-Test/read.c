/** *******************************************************
 * 
 * includes the function definitions for reading a csv file
 * 
 */



#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#include "list.h"
#include "read.h"

/** *******************************************************/

#define KEY_LENGTH 129
#define TRUE 1
#define FALSE 0

/** *******************************************************/

/* function to read a csv file and assign key */
void read_key(dict_t *dict, char *columns, FILE *fp_out) {

    char key[KEY_LENGTH];

    while(fgets(key, KEY_LENGTH, stdin)) {
        /* terminate the string and delete the newline character */
        key[strlen(key) - 1] = '\0';

        dict_search(dict, key, columns, fp_out);
    }
}

/* function to scan the keys from standard input */
int read_first_row(char *key, char *columns, FILE *fp_in) {

    char c;
    int num_commas = 0;
    int i = 0, j = 0;

    /* read a line of the csv file */
    while((c = fgetc(fp_in)) && c != '\n' && c != EOF && c != '\r') {

        /* arrived at the key column */
        if(num_commas == 5) {
            j = 0;
            key[j++] = c;

            /* copy column name into key */
            while((c = fgetc(fp_in)) && c != ',') key[j++] = c;

            num_commas++;
            continue;
        }

        if(c == ',') num_commas++;

        columns[i++] = c;
    }

    /* terminate the strings */
    columns[i] = '\0';
    key[j] = '\0';

    if(c == EOF) return FALSE;

    return TRUE;

}

/* function to read the column headers of a csv file */
int read_csv(char *key, char *value, char *column, FILE *fp_in) {

    char c;
    int num_commas = 0;

    int i = 0, j= 0;

    /* read a line of the csv file */
    while((c = fgetc(fp_in)) && c != '\n' && c != EOF && c != '\r') {

        /* arrived at the key column */
        if(num_commas == 5) {
            j = 0;
            if(c == '"') {
                while((c = fgetc(fp_in))) {
                    if(c == '"') {

                        /* check if at end of column name */
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

            /* copy column name into key */
            while((c = fgetc(fp_in)) && c != ',') key[j++] = c;
            
            num_commas++;
            continue;
        }
        else{

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
    key[j] = '\0';

    if(c == EOF) return FALSE;

    return TRUE;
}