#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    struct stat infos;
    int c;
    if(stat(argv[1], &infos) == -1){
        perror("stat");
        exit(EXIT_FAILURE);
    }


    if(S_ISDIR(infos.st_mode)){
        c = 'd';
    }
    else if(S_ISREG(infos.st_mode)){
        c = 'f';
    }
    else{
        c = '?';
    }
    printf("type of file : %c\n", c);
    printf("last date modification : %s", ctime(&infos.st_mtim.tv_sec));
    printf("size : %lld bytes\n", (long long) infos.st_size);



    return 0;
}
