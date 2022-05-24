#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../try.h"

struct winsize ws;

//référence exo 1 TP7

void handler(int sig){

    switch(sig){
        case SIGWINCH:
            try(ioctl(STDIN_FILENO, TIOCGWINSZ, &ws));
            printf("Window size %d x %d\n", ws.ws_row, ws.ws_col);
            break;
        case SIGINT:
            printf("This program wont stop\n");
            break;
    }


}

int exo1(void){
    try(signal(SIGWINCH, handler), SIG_ERR);
    try(signal(SIGINT, handler), SIG_ERR);
    while(1);
    return 0;
}


int exo2(void){

}

int main(int argc, char const *argv[])
{
    return 0;
}
