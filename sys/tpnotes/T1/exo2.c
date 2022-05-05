#include <stdio.h>
#include <stdlib.h>
#include "try.h"
#include <sys/wait.h>

//Exercice 2 tp noté 2020

int main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(stderr, "not enough args given\n");
        return EXIT_FAILURE;
    }
    
    while(1){
        switch(try(fork())){
            case 0:
                try(execvp(argv[1], argv+1));
                break;
            default:
                sleep(1);
                break;
        }
    }
    return 0;
}
