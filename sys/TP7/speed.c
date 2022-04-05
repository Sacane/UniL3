#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <string.h>
#include <unistd.h> 
#include "../try.h"

struct sigaction s;
ssize_t read_bytes = 0;
int is_alarm_activated = 0;


void signal_handler(int signo) {

    
    is_alarm_activated = 1;
    try(alarm(1));
    
    
}

int main(int argc, char **argv) {

    
    char buffer[32];
    int signo = SIGALRM; 

    try(sigemptyset(&s.sa_mask));
    s.sa_handler = signal_handler;
    s.sa_flags = 0;

    try(sigaction(SIGALRM, &s, NULL));


    try(alarm(1));

    while(1) {
        
        read_bytes += (read(STDIN_FILENO, buffer, 32));
        if(is_alarm_activated){
            printf("%ld B/s\n", read_bytes);
            read_bytes = 0;
            is_alarm_activated = 0;
        }
        
        
    }

    return 0;
}