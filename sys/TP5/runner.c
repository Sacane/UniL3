#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../try.h"
#include <fcntl.h>


int main(int argc, char *const argv[])
{
    int wstatus;
    pid_t pid;
    int fd;
    
    if(argc < 2){
        printf("Not good usages !!\n");

        return 1;
    }
    
    
    switch(try(fork())){
        case 0:
            fd = try(open("/dev/null", O_WRONLY));
            try(dup2(fd, STDOUT_FILENO));
            try(execvp(argv[1], argv+1));
            break;
        default:
            wait(&wstatus);
            printf("%s\n", (!WEXITSTATUS(wstatus)) ? "GOOD" : "ERROR");
            break;
    }


    return 0;
}
