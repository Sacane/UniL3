#include <stdio.h>
#include <unistd.h>
#include "../try.h"
#include <sys/wait.h>


void ls(){
    char *args[3];
    args[0] = "ls";
    args[1] = NULL;
    args[2] = NULL;
    try(execvp("ls", args));
}

void ps(){
        
    char *args[3];
    args[0] = "ps";
    args[1] = NULL;
    args[2] = NULL;
    try(execvp("ps", args));
}

void l_free(){
    char *args[3];
    args[0] = "free";
    args[1] = NULL;
    args[2] = NULL;
    try(execvp("free", args));
}

int main(int argc, char const *argv[])
{

    
    switch(try(fork())){
        case 0: 
            switch(try(fork())){
                case 0: 
                    usleep(1000);
                    ps();
                    break;
                default: 
                    ls();
                    break;
            }
            break;
        default:
            try(wait(NULL));
            l_free();
    }

    return 0;
}
