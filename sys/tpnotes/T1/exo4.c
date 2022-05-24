#include <stdio.h>
#include <stdlib.h>
#include "try.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//exercice 4 2020 

int main(int argc, char const *argv[])
{
    char buf[BUFSIZ];
    if(argc < 2){
        fprintf(stderr, "not enough args given\n");
        return EXIT_FAILURE;
    }

    struct stat statbuf;
    try(lstat(argv[1], &statbuf));
    printf("Name : %s | Inode number : %d |size : %ld\n", argv[1], (int)statbuf.st_ino, (long)statbuf.st_size);
    if(S_ISLNK(statbuf.st_mode)){
        readlink(argv[1], buf, BUFSIZ);
        printf("Reference du lien : %s\n", buf);
    }

    return 0;
}