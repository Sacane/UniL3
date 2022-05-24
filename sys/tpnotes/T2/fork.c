#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include "../try.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

//ref tpNote 2020 exercice 1

void tableOf(int n){
    for(int i = 0; i < 101; i++){
        printf("%d x %d = %d\n", i, n, i * n);
    }
}


int main(int argc, char const *argv[])
{
    switch(try(fork())){
        case 0: //Proc fils
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
