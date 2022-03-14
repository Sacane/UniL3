#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../try.h"
#include <sys/wait.h>
#include <ctype.h>


int exec_pip(void) {
    char c;
    int p[2];
    try(pipe(p));
    try(fcntl(p[1], F_SETFL, O_NONBLOCK));
    size_t i;
    for (i = 0; write(p[1], "#", 1) != -1; i++) {}
    read(p[0], &c, 1);
    printf("The pipe capacity is %ld bytes. %c\n", i, c);
    return 0;
}


int main(int argc, char const *argv[])
{
    int entry;
    char c, c_parent;
    int p[2];
    try(pipe(p));
    size_t i;

    switch(try(fork())){
        case 0:
            try(close(p[0]));
            do{
                c = fgetc(stdin);
                c = toupper(c);
                try(write(p[1], &c, 1));

            }while(c != -1); //end with EOF
            break;
        default:
            try(close(p[1]));
            wait(NULL);
            while(try(read(p[0], &c_parent, 1))){
                try(write(1, &c_parent, 1));
            }
            break;
    }

    return 0;
}



