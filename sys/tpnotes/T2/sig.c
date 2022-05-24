#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../try.h"


int main(void) {
    pid_t pid;
    switch (pid = try(fork())) {
    case 0: // Child
    while (1) {
        try(write(1, "#", 1));
        usleep(30000); 
    } break;
    default: // Parent
        while (1) {
            try(kill(pid, SIGCONT));
            sleep(1);
            try(kill(pid, SIGSTOP));
            sleep(3); 
        } 
        break;
    }
}
