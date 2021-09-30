#include <stdio.h>
#include <stdlib.h>


float pgcd(int a, int b){
    int x, y, r;
    x = a;
    y = b;
    while(y != 0){
        r = x%y;
        x = y;
        y = r;
    }
    return x;
}

/* Return the ppcm between 2 integers */
int ppcm(int a, int b){
    return (a*b)/(pgcd(a, b));
}

/* Return the ppcm between an array of integers */
int findPpcm(int * tab, int size){
    
    int i, res;
    
    if(size == 2){
        return tab[0];
    }
    
    res = ppcm(tab[0], tab[1]);

    for(i = 1; i < size - 1; i++){
        res = ppcm(res, tab[i]);
    }

    return res;
}

int main(int argc, char ** argv){
    int i;
    
    int* numbers = malloc(sizeof(int*)*argc);
    for(i = 0; i < argc-1; i++){
        numbers[i] = atoi(argv[i+1]);
    }
    
    int res = findPpcm(numbers, argc);
    printf("%d\n", res);
    free(numbers);
    return 0;
}