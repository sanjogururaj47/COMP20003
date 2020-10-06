#include <stdlib.h>
#include <stdio.h>

/* Define an I, which will be the size of the array, A. */
#define I 7
#define STRINGLENGTH 2

int main(int argc, char **argv){
    /* Define an array, A, of integers */
    /* write a loop which populates A with multiples of 12 */
    /* print out A[0], A[2] and A[5] */
    
	int i,j;
	char A[I][STRINGLENGTH + 1];
	
	for(i = 0; i < I; i++){
		for(j = 0; j < STRINGLENGTH; j++){
			scanf("%c",&(A[i][j]));
		}
		A[i][STRINGLENGTH] = '\0';
	}
	
	printf("%s\n",A[0]);
	printf("%s\n",A[2]);
	printf("%s\n",A[5]);
	
    return 0;
}
