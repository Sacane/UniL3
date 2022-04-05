#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../try.h"
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>
#include <signal.h>

static struct winsize ws;
struct sigaction sig;

void handler(int sig){
    try(ioctl(STDIN_FILENO, TIOCGWINSZ, &ws));
    printf("Window size %d x %d\n", ws.ws_col, ws.ws_row);
}

int main(int argc, char const *argv[])
{
    sig.sa_handler = handler;
    sig.sa_flags = 0;
    try(sigaction(SIGWINCH, &sig, NULL), SIG_ERR);

    

    while(1);

    return 0;
}
