#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "../try.h"
#define N 10000


void stat_apply(char const *path){
    struct stat sb;
    int c;
    char type;
    int is_link = 0;
    char buf_link[BUFSIZ];
    int ret;


    try(lstat(path, &sb));



    switch(sb.st_mode & S_IFMT){

        case S_IFDIR: /* Directory */
            type = 'd';
            break;
        case S_IFREG: /* Regular File */
            type = 'f';
            break;
        case S_IFLNK:
            is_link = 1;
            break;
        default: /* Other Type */
            type = '?';
            break;
    }

    if(is_link){
        ret = try(readlink(path, buf_link, BUFSIZ));
        if(ret != -1){
            printf("%s\n", buf_link);
        }
        printf("l\n");
    }
    printf("type of file : %c\n", type);
    printf("last date modification : %s", ctime(&sb.st_mtim.tv_sec));
    printf("size : %lld bytes\n", (long long) sb.st_size);
}


int main(int argc, char const *argv[])
{

    if(argc != 2){
        printf("This program needs an argument\n");
        return 1;
    }
    stat_apply(argv);

    return 0;
}