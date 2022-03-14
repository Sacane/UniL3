#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../try.h"


int main(int argc, char const *argv[])
{
    int wstatus;
    pid_t pid;
    if(argc < 2){
        printf("Not good usages\n");
        return 1;
    }
    

    switch(try(fork())){
        case 0:
            try(execvp(argv[1], argv+1));

        default:;
            wait(&wstatus);
            if(!WEXITSTATUS(wstatus)){
                printf("GOOD\n");
            }
            else{
                printf("ERROR\n");
            }
            break;
    }


    return 0;
}
