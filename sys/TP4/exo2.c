#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include "../try.h"

int main(int argc, char const *argv[])
{
    pid_t pid;
    char buffer[50];
    const char* messageWithWrite = "My PID is";
    pid = (long) getpid();
    sprintf(buffer, "%s %ld", messageWithWrite, (long)pid);
    printf("mon PID est %ld", (long) pid);
    write(STDOUT_FILENO, buffer, 14);
    
    switch (try(fork()))
    {
    case 0:
        pid = getpid();
        sprintf(buffer, "I'm the children and my pid is %ld", (long)pid);
        printf("Je suis l'enfant et mon pid est : %ld", (long)pid);
        write(STDOUT_FILENO, buffer, 40);

        break;
    
    default:
        pid = getpid();
        sprintf(buffer, "I'm the parent and my pid is %ld", (long)pid);
        printf("Je suis le parent et mon pid est : %ld", (long)pid);
        write(STDOUT_FILENO, buffer, 40);
        break;
    }
    puts("\n");


    return 0;
}
