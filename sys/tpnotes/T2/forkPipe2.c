#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include "../try.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

#define WRITE_SIDE 1
#define READ_SIDE 0

int main(int argc, char const *argv[])
{
    
    int p[2];
    int c;
    int getter;

    try(pipe(p));
    while(1){
        switch(try(fork())){
            case 0:
                try(close(p[READ_SIDE]));

                do {
                    c = fgetc(stdin);
                    c = toupper(c);
                    try(write(p[WRITE_SIDE], &c, sizeof(char)));
                }while(c != '\n');
                break;

            default:
                try(close(p[WRITE_SIDE]));
                
                while(try(read(p[READ_SIDE], &getter, sizeof(char)))){
                    try(write(STDOUT_FILENO, &getter, sizeof(char)));
                }
                break;
        }
    }



    return 0;
}
