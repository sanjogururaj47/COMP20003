#ifndef READ_H_INCLUDED
#define READ_H_INCLUDED

/* function to read a csv file and assign key */
int read_csv(char *key, char *value, char *column, FILE *fp_in);

/* function to scan the keys from standard input */
void read_key(dict_t *dict, char *columns, FILE *fp_out);

/* function to read the column headers of a csv file */
int read_first_row(char *key, char *columns, FILE *fp_in);

#endif