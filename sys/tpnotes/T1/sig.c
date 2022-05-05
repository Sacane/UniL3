#include <stdio.h>
#include <stdlib.h>
#include "try.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <signal.h>

//Exercice 1 TP7 : Signaux
struct winsize ws;

void handler(int sig){
    switch(sig){
        case SIGWINCH:
            try(ioctl(STDIN_FILENO, TIOCGWINSZ, &ws));
            printf("shell size : %d x %d\n", ws.ws_col, ws.ws_row);
            break;
        case SIGINT:
            printf("Tried to end process\n");
            break;
        default:
            break;
    }
}

int main(int argc, char const *argv[]){
    
    signal(SIGWINCH, handler);
    signal(SIGINT, handler);


    try(ioctl(STDIN_FILENO, TIOCGWINSZ, &ws));
    printf("shell size : %d x %d\n", ws.ws_col, ws.ws_row);
    while(1){}
    return 0;
}


