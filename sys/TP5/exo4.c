#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../try.h"
#include <sys/wait.h>
#include <ctype.h>

void on_baby_death()
{
    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    
    int entry;
    char c;
    int p[2];
    try(pipe(p));
    char buf[BUFSIZ];
    int currsize;

    signal(SIGCHLD, on_baby_death);
    
    switch(try(fork())){
        case 0:
            try(close(p[1]));
            currsize = 0;
            while(currsize < 10){
                try(read(p[0], &c, 1));
                try(write(1, &c, 1));
                currsize++;
            }
            break;
        default:
            try(close(p[0]));
            do{
                c = fgetc(stdin);
                try(write(p[1], &c, 1));

            }while(c != -1); 

            break;
    }

    return 0;
}
