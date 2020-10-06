#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Define an I, which will be the size of the array, A. */
#define I 7

struct node {
	struct node *next;
	char *string;
};

int main(int argc, char **argv){
    /* Define an array, A, of integers */
    /* write a loop which populates A with multiples of 12 */
    /* print out A[0], A[2] and A[5] */
    
	int i,j;
	int size;
	struct node *head = NULL;
	struct node *current = NULL;
	
	for(i = 0; i < I; i++){
		current = (struct node *) malloc(sizeof(struct node));
		assert(current);
		
		scanf("%d",&size);
		current->string = (char *) malloc(sizeof(char)*(size + 1));
		assert(current->string);
		
		current->next = head;
		head = current;
		
		for(j = 0; j < size; j++){
			scanf("%c",&((current->string)[j]));
		}
		(current->string)[size] = '\0';
	}
	
	printf("%s\n",current->string);
	printf("%s\n",current->next->string);
	printf("%s\n",current->next->next->string);
	
	current = head;
    while(current){
        head = current;
        free(current->string);
        current = current->next;
        free(head);
    }
	
    return 0;
}
