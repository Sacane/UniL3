#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "../try.h"


int main(int argc, char const *argv[])
{
    sig_t sig;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    
    return 0;
}
