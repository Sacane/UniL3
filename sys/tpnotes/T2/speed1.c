#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include "../try.h"

ssize_t bytes;

//Ref : TP7 exo 2.1

void handler(int sig){
    if(sig == SIGALRM){
        printf("%ld B/s\n", bytes);
        bytes = 0;
    }

}

int main(int argc, char const *argv[])
{
    char buf[BUFSIZ];
    ssize_t tmp;
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_handler = handler;
    act.sa_flags = 0;

    try(sigaction(SIGALRM, &act, NULL));

    //equivalent : try(signal(SIGALRM, handler));
    

    try(alarm(1));

    while(1){
        bytes += read(STDIN_FILENO, buf, BUFSIZ);
    }


    return 0;
}
