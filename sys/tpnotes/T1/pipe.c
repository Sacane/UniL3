#include <stdio.h>
#include <stdlib.h>
#include "try.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#define WRITE 1
#define READ 0


//Exercice 3 tp5 : pipe

int main(int argc, char const *argv[])
{   
    int p[2];
    char *s;
    char c;
    char c2;
    int wstatus;
    try(pipe(p));
    
    switch(try(fork())){
        case 0:
            try(close(p[READ]));
            do{
                c = fgetc(stdin);
                c = toupper(c);
                try(write(p[1], &c, 1));
            }while(c != '\n');
            break;
        default:   
            try(close(p[WRITE]));
            wait(&wstatus);
            if(!WIFEXITED(wstatus)){
                printf("erreur de renvoi du caractère\n");
            }
            else {
                printf("le pipe s'est bien déroulé !\n");
            }
            while(try(read(p[0], &c, 1))){
                try(write(STDOUT_FILENO, &c, 1));
            }
            break;
    }
    return 0;
}