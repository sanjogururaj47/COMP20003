#ifndef _DATA_H_
#define _DATA_H_

#include "utils.h"

#define C ','     
#define Q '\"'   
#define NL '\n' 
 
#define FIELD_LEN 128

// Note: it's more convenient to typedef data_t as char**
//       but the requirement is to use struct ;-(
typedef struct {
	char *year, *bid, *pid, *bpid;  // 0-3
	char *clue, *name;              // 4, 5
	char *code;                     // 6
	char *desc;                     // 7
	char *x, *y;                    // 8,9
	char *loc;                      // 10;
} data_t;

void print_data(data_t *d, FILE *f);  // print a data to file f
void free_data(data_t *d);            // 
data_t *get_next_data(FILE *f);       // return a next record read from f

void data_get_header(FILE *f);       // get rid off & and store header for late use
void data_free_header();             // free the sored header

char *getfield(FILE *f, char deli);  // get a next field from file f
#endif
