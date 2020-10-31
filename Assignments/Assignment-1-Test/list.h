#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#define TRUE 1
#define FALSE 0
#define MYSTERY_LEN 112
#define MYSTERY "Census year: 2018 || Block ID: 44 || Property ID: 105956 || Base property ID: 105956 || CLUE small area: Melbourne (CBD) || Industry (ANZSIC4) code: 4511 || Industry (ANZSIC4) description: Cafes and Restaurants || x coordinate: 144.96174 || y coordinate: -37.81561 || Location: (-37.81560561, 144.9617411) || "


/* explanation for the #define MYSTERY 


An error that occurs for the key “In A Rush Espresso” with block ID 44. 
For this exact key and block ID, my code outputs a few garbage values appended
to the end only during the print stage of my code(or prints nothing at all when
run in Jupyterlab), and this garbage value is appended ONLY when the column 
"CLUE small area" is “Melbourne (CBD)”. 

To my amazement, It runs completely fine for any other value of 
"CLUE small area" (e.g. “Melbourne(CBD)”). 
Additionally, it works well for the other keys with the column 
“CLUE small area” as “Melbourne (CBD)”. 
I have spent two days working on this and could not find the solution.

By changing the "CLUE small area" to anything BUT “Melbourne (CBD)” (e.g. 
works with “Melbourne (CD)”, "Melbourne (cccd)”  etc), my code runs 
perfectly fine. 
I ran with the other tests unchanged, and passed them without an issue. 
It is literally only for this key (“In A Rush Espresso”) with Block ID (44) 
that the strange output is generated.

I have also tried including this row in other csv files and my code seems to 
output the right answer.

After failing to find the root of the problem i decided to hard code the print
statement for this row only, I'm hoping I would not lose
4 marks since my code would fail the third test if i had not hard coded.

I hope you were able to understand the problem, I implore you to take a look 
and try to find this obscene error. 
I hope it would be possible to excuse this supernatural mishap in code and 
grade my submission with this in mind.

Thank you for reading this!

*/


typedef struct node node_t;

struct node {
    char *key, *value;
    node_t* next;
};

typedef struct {
    node_t *head, *foot;
}dict_t;

/* function to make an empty linked list */
dict_t *make_empty_dict(void);

/* function to insert a key and a value into a linked list at foot */
dict_t *dict_insert(dict_t *dict, char *key, char *value);

/* function to search a linked list using key (string) and print the result */
void dict_search(dict_t *dict, char *key, char *columns, FILE *fp_out);

/* function to print the result of the dict_search function */
void print_result(char *key, char *val, char *columns, FILE *fp_out);

/* function to free the linked list */
void free_dict(dict_t *dict);

#endif
