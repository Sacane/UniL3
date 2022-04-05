#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../try.h"
#include <sys/wait.h>
#include <ctype.h>


int main(int argc, char const *argv[])
{
    int entry;
    char c, c_parent;
    int p[2];
    try(pipe(p));
    size_t i;
    //Writer is children, p[1] => to write and p[0] => to read
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



