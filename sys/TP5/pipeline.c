#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../try.h"
#include <sys/wait.h>
#include <ctype.h>



int main(int argc, char const *argv[])
{
    int p[2], i;
    char buf[BUFSIZ];
    try(pipe(p));

    if (argc <= 2){
        return 1;
    }

    for(i = 0; i < argc; i++){
        
        switch(try(fork())){
            case 0:
                try(close(p[0]));
                dup2(p[1], STDOUT_FILENO);
                execlp(argv[1], argv[1], (char*)NULL);
                break;
            default:
                try(close(p[1]));
                wait(NULL);
                dup2(p[0], STDIN_FILENO);
                execlp(argv[2], argv[2], (char*) NULL);
                
                break;
        }
    }



    return 0;
}
