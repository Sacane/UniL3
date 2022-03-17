#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../try.h"
#include "sys/wait.h"
#define NAME "RUN_"



void exec(char *cmd, char **args){
    sprintf(*args, "%s", cmd);
    execvp(cmd, args);
}

void exec_env(char **argv){
    char key[6], *value;
    
    int i = 0;

    
    do {
        
        sprintf(key, "%s%d", NAME, i);
        
        value = getenv(key);

        if(value == NULL){
            break;
        }
    


        switch(try(fork())){
            case 0:
                exec(value, argv);
                break;
            default:
                wait(NULL);
                break;
        }

        

        i++;

    }while(1);
}

void print_env(){
    char key[6], *value;

    int i = 0;


    
    do {

        sprintf(key, "%s%d", NAME, i);


        value = getenv(key);
        if(value == NULL){
            printf("NO VARIABLE EXISTING FOR %s\n", key);
            break;
        }
        
        printf("Env : %s = %s\n", key, value);

        i++;

    }while(1);
}

int main(int argc, char **argv)
{


    exec_env(argv);





    return 0;
}
