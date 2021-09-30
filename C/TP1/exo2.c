#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

/*
 * complexity : O(n)²
*/
int bin(int n, int p){
    assert(p <= n);
    assert(n > 0);
    if(p == 0 || n == p){
        return 1;
    }
    return bin(n - 1, p) + bin(n - 1, p - 1);
}

/*
*/
int** binTab(int n, int p){
    int i;
    int j;
    
    assert(p <= n);
    int **tab = malloc(sizeof(int **)*n);
    for(i = 0; i < n; i++){
        tab[i] = malloc(sizeof(int*)*p);
        tab[i][0] = 1;
        for(j = 0; j < p; j++){
            if(j > 0 && i > 0){
                tab[i][j] = tab[i - 1][j] + tab[i - 1][j - 1];
            }
        }
    }
    return tab;
}

int main(int argc, char **argv){
    time_t begin, end;
    unsigned long t_f1, t_f2;
    int test_bin, test_tab;

    int n = 7;
    int p = 7;
    int **tab = binTab(n, p);
    int i, j;
    begin = time(NULL);
    for(i = 0; i < n; i++){
        for(j = 0; j < p; j++){
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    end = time(NULL);
    t_f2 = (unsigned long) difftime(end, begin);

    
    begin = time(NULL);
    test_bin = bin(6, 3);
    end = time(NULL);
    t_f1 = (unsigned long) difftime(end, begin);

    printf("t_f1 : %ld t_f2 : %ld\n", t_f1, t_f2);

    for(i = 0; i < n; i++){
        free(tab[i]);
    }
    free(tab);

    return 0;
}