#include <stdio.h>
#include <stdlib.h>
#include "try.h"
#include <sys/wait.h>

//Exercice 1 tp noté 2020

void tableOf(int table){
    for(int i = 1; i < 101; i++){
        printf("%d x %d = %d\n", i, table, i * table);
    }
}

int main(int argc, char const *argv[])
{   

    switch(try(fork())){
        case 0:
            tableOf(5);
            break;
        default:
            tableOf(7);
            wait(NULL);
            printf("Fin du calcul\n");
            break;
    }
    
    return 0;
}
