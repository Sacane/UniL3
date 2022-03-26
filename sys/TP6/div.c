#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{
    int n, n2;
    while(1){
        scanf("%d\n", &n);
        scanf("%d\n", &n2);
        if(n2 == 0){
            printf("Error, dividende can't be 0\n");
            return 1;
        }
        printf("Resultat : %d\n", n / n2);

        fflush(stdout);
    }
    return 0;
}
