#include <stdio.h>
#include <stdlib.h>
#define PRIMECOUNT 1000

int main(int argc, char **argv){
    /* The primes 1 - 1000, if n is prime, 
        primes[n - 1] == 1 and 0 otherwise. */
    int primes[PRIMECOUNT];
    int i,j;
    
    for(i = 0; i < PRIMECOUNT; i++){
        primes[i] = 1;
    }
    
    /* Write a prime checking algorithm here. */
    for(i = 1; i < PRIMECOUNT; i++){
        for(j = i+1; j < PRIMECOUNT; j++){
            if(primes[j]){
                if((j + 1) % (i + 1) == 0){
                    primes[j] = 0;
                }
            }
        }
    }
    /* -------------------------------------- */
    
    printf("All primes found from 1 - 1000:\n");
    for(i = 0; i < PRIMECOUNT; i++){
        if(primes[i]){
            printf("%d ",i + 1);
        }
    }
    printf("\n");
    
    return 0;
}
