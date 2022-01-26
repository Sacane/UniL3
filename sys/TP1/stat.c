#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../try.h"

void stat_apply(char const *argv[]){
    struct stat sb;
    int c;
    char type;


    try(stat(argv[1], &sb));



    switch(sb.st_mode & S_IFMT){

        case S_IFDIR: /* Directory */
            type = 'd';
            break;
        case S_IFREG: /* Regular File */
            type = 'f';
            break;
        default: /* Other Type */
            type = '?';
            break;
    }

    printf("type of file : %c\n", type);
    printf("last date modification : %s", ctime(&sb.st_mtim.tv_sec));
    printf("size : %lld bytes\n", (long long) sb.st_size);
}


int main(int argc, char const *argv[])
{

    stat_apply(argv);

    return 0;
}
