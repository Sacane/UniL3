#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include "../try.h"
#include "string.h"



typedef struct stat_info{

    char type;
    int is_link;
    char buf_link[BUFSIZ];
    char last_date_modification[BUFSIZ];
    long long size;

}Info;

void print_infos(Info info){
    if(info.is_link){
        printf("%s\n", info.buf_link);
    }
    printf("type of file : %c\n", info.type);
    printf("last date modification : %s", info.last_date_modification);
    printf("size : %lld bytes\n", info.size);
}

Info stat_apply(char const *path){
    Info info;
    struct stat sb;
    int c;
    char type;
    int is_link = 0;
    char buf_link[BUFSIZ];
    int ret;


    try(lstat(path, &sb));



    switch(sb.st_mode & S_IFMT){

        case S_IFDIR: /* Directory */
            info.type = 'd';
            type = 'd';
            break;
        case S_IFREG: /* Regular File */
            info.type = 'f';
            break;
        case S_IFLNK:
            is_link = 1;
            break;
        default: /* Other Type */
            info.type = '?';
            break;
    }

    if(is_link){
        ret = try(readlink(path, buf_link, BUFSIZ));
        if(ret != -1){
            strcpy(info.buf_link, buf_link);
        }
    }


    strcpy(info.last_date_modification, ctime(&sb.st_mtim.tv_sec));
    info.size = (long long) sb.st_size;
    return info;
}

int main(int argc, char const *argv[])
{
    int is_file = 0;
    int is_directory = 0;
    int i;
    const char *first_arg = (argc < 2) ? "." : argv[1];



    DIR *dir;
    struct dirent *directory;
    
    printf("%s\n", first_arg);
    Info info;



    if(argc < 2){
        dir = try(opendir("."), NULL);
        while((directory = readdir(dir)) != NULL){
            info = stat_apply(directory->d_name);
            if(strcmp(directory->d_name, ".") == 0 || strcmp(directory->d_name, "..") == 0){
                continue;
            }
            else{
                printf("Name : %s\n", directory->d_name);
                print_infos(info);
            }
            printf("\n");
        }

        closedir(dir);
        return 0;
    }
    
    for(i = 1; i < argc; i++){
        info = stat_apply(argv[1]);
        printf("%c\n", info.type);
        switch(info.type){
            case 'f':
                is_file = 1;
                print_infos(info);
                is_directory = 0;
                break;
            case 'd':
                is_directory = 1;
                is_file = 0;
                break;
            default:
                break;
        }
    
    
        
        if(is_file) return 0;

        if(is_directory){
            dir = try(opendir(argv[i]), NULL);
            while((directory = readdir(dir)) != NULL){
                info = stat_apply(directory->d_name);
                printf("directory : %s\n", directory->d_name);
                if(strcmp(directory->d_name, ".") == 0 || strcmp(directory->d_name, "..") == 0){
                    continue;
                }
                else{
                    printf("Name : %s\n", directory->d_name);
                    print_infos(info);
                }
                printf("\n");
            }

            closedir(dir);
        }
    }

    return 0;
}
