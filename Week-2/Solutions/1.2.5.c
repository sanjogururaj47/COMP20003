#include <stdlib.h>
#include <stdio.h>

/* Define an I, which will be the size of the array, A. */
#define I 7

int main(int argc, char **argv){
    /* Define an array, A, of integers */
    /* write a loop which populates A with multiples of 12 */
    /* print out A[0], A[2] and A[5] */
    
	int i,j;
	int size;
	char *A[I];
	
	for(i = 0; i < I; i++){
		scanf("%d",&size);
		A[i] = (char *) malloc(sizeof(char)*(size + 1));
		for(j = 0; j < size; j++){
			scanf("%c",&(A[i][j]));
		}
		A[i][size] = '\0';
	}
	
	printf("%s\n",A[0]);
	printf("%s\n",A[2]);
	printf("%s\n",A[5]);
	
	for(i = 0; i < I; i++){
        free(A[i]);
    }
	
    return 0;
}
