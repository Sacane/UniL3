#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*  */
float harmony_f(int n){
    assert(n != 0);
    float res = 0.0;
    int i;
    for(i = 1; i < n; i++){
        res += (1.0 / i);
    }
    return res;
}
double harmony_d(int n){
    assert(n != 0);
    double res = 0.0;
    int i;
    for(i = 1; i < n; i++){
        res += (1.0 / i);
    }
    return res;
}

/* 
This program wait an argument which will be use for
the iteration to do the harmony series
*/
int main(int argc, char const *argv[])
{
    int i, n;
    if(argc < 2 || !(n = atoi(argv[1]))){
        n = 10000;
    }
    printf("%d\n", n);
    for(i = 1; i <= n; i++){
        if(i % 10000 == 0){
            printf("As float : %d : %f\n", i, harmony_f(i));
            printf("As double : %d : %lf\n", i, harmony_d(i));
        }
    }
    return 0;
}
