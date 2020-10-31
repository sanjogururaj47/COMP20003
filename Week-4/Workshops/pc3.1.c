#include <stdio.h>
#include <stdlib.h>
#define GRUDGECOUNT 5
#define NATIONS 8
#define PARTNERS 2
#define GROUPS NATIONS/PARTNERS

void findpairs(int grudges[GRUDGECOUNT][PARTNERS], int pairs[GROUPS][PARTNERS], int decided, int *present);

int conflict(int grudges[GRUDGECOUNT][PARTNERS], int pairs[GROUPS][PARTNERS]);

int main(int argc, char **argv){
    int grudges[GRUDGECOUNT][PARTNERS];
    int pairs[GROUPS][PARTNERS];
    int i, j;
    
    /* 
        Grudges are:
        3 and 4
        5 and 6
        1 and 3
        2 and 3
        3 and 6
    */
    
    grudges[0][0] = 3; grudges[0][1] = 4;
    grudges[1][0] = 5; grudges[1][1] = 6;
    grudges[2][0] = 1; grudges[2][1] = 3;
    grudges[3][0] = 2; grudges[3][1] = 3;
    grudges[4][0] = 3; grudges[4][1] = 6;
    
    /* Find pairs using some algorithm. */
    int present[NATIONS];
    findpairs(grudges, pairs, 0, present);
    
    /* -------------------------------- */
    for(i = 0; i < GROUPS; i++){
        printf("Partners %d: ",i);
        for(j = 0; j < PARTNERS; j++){
            if(j != 0){
                printf(" and ");
            }
            printf("%d",pairs[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

void findpairs(int grudges[GRUDGECOUNT][PARTNERS], int pairs[GROUPS][PARTNERS], int decided, int *present){
    int i, j;
    int nextUnused = 0;
    if(decided == 0){
        /* First loop, reset all pairs */
        for(i = 0; i < GROUPS; i++){
            for(j = 0; j < PARTNERS; j++){
                pairs[i][j] = -1;
            }
        }
        for(i = 0; i < NATIONS; i++){
            present[i] = 0;
        }
    }
    for(i = 0; i < NATIONS; i++){
        if(!present[i]){
            pairs[decided / PARTNERS][decided % PARTNERS] = i;
            present[i] = 1;
            /* Check this change hasn't caused any issues, 
                if it has, undo what we've done and try the next one. */
            if(conflict(grudges, pairs)){
                present[i] = 0;
                /* Done with this loop. */
                continue;
            }
            if(decided < NATIONS){
                findpairs(grudges, pairs, decided + 1, present);
            }
            /* Check if all present, if so, we're done, return, 
               otherwise continue. */
            for(j = 0; j < NATIONS; j++){
                if(present[j] == 0){
                    /* Found a nation which isn't paired, undo
                        current present and continue. */
                    present[i] = 0;
                    continue;
                }
            }
            /* Found solution. all done. */
            return;
        }
    }
}

int conflict(int grudges[GRUDGECOUNT][PARTNERS], int pairs[GROUPS][PARTNERS]){
    int i,j,k,l;
    int count;
    for(i = 0; i < GROUPS; i++){
        /* Check not all partners in ith group not a grudges group */
        for(j = 0; j < GRUDGECOUNT; j++){
            count = 0;
            /* Accumulate all partners. */
            for(k = 0; k < PARTNERS; k++){
                for(l = 0; l < PARTNERS; l++){
                   if(grudges[j][k] == pairs[i][l]){
                       count++;
                       break;
                   }
                }
                if(count >= PARTNERS){
                    return 1;
                }
            }
        }
    }
    /* Found no conflicts */
    return 0;
}