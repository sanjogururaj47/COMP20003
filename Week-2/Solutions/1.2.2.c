#include <stdlib.h>
#include <stdio.h>

/* Define an I, which will be the size of the array, A. */
#define I 10

int main(int argc, char **argv){
    /* Define an array, A, of integers */
    /* write a loop which populates A with multiples of 12 */
    /* print out A[0], A[2] and A[5] */
    
	int i;
	int A[I];
	
	for(i = 0; i < I; i++){
		A[i] = rand();
	}
	
	printf("%d\n",A[0]);
	printf("%d\n",A[2]);
	printf("%d\n",A[5]);
	
    return 0;
}
