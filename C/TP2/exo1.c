#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* This program check the property : n = x^3 + y^3 + z^3 for the numbers (i) between 0 and 500*/
int main(int argc, char const *argv[])
{
    int x, y, z, i, n;

    for(i = 0; i <= 500; i++){
        x = i / 100;
        y = i / 10 % 10;
        z = i % 10;
        n = pow(x, 3) + pow(y, 3) + pow(z, 3);
        if(i == n){
            printf("%d\n", n);
            printf("x : %d, y : %d, z : %d\n", x, y, z);
        }
    }
    return 0;
}
