#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include "try.h"

sig_atomic_t __flag_alarm = 0;

//ref : exo2.2 TP7

void handler_SIGALRM(int sig) {
    __flag_alarm = 1;
    alarm(1);
}

int main(int argc, char const *argv[])
{
    char buf[1024];
    int temp, cpt = 0;
    struct sigaction act = {.sa_handler = handler_SIGALRM};
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    try(sigaction(SIGALRM, &act, NULL));

    try(alarm(1));
    
    while (1) {
        temp = try(read(STDIN_FILENO, buf, 1024));

        if (temp != -1) {
            cpt += temp;
        }

        if (__flag_alarm) {
            __flag_alarm = 0;
            printf("Speed : %d B/s\n", cpt);
            cpt = 0;

        }
    } 
    return 0;
}