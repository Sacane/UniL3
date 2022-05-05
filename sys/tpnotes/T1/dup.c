#include <stdio.h>
#include <stdlib.h>
#include "try.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

/* Reference exercice 1 tp5 */

int main(int argc, char const *argv[])
{
    int fd;
    if(argc < 2){
        fprintf(stderr, "not enough args given\n");
        return EXIT_FAILURE;
    }
    
    fd = try(open(argv[1], O_WRONLY));

    //Redirection de Stdout vers le fichier indiqué en argument
    try(dup2(fd, STDOUT_FILENO));
    
    //execution de ls
    try(execlp("ls", "ls", "-l", (char *)NULL));

    try(close(fd));

    return 0;
}
