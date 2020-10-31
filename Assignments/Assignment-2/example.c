#include<stdio.h>

int func(int *i) {
    

    
    if(*i == 100) {
        return *i;
    }
    *i += 10;
    func(i);
    printf("i: %d\n", *i);
    return *i;
}

int main(int argc, char **argv) {
    //func(0);
    int a = 0;
    func(&a);
    printf("\n\n\n\n\na: %d", a);
    return 0;
}