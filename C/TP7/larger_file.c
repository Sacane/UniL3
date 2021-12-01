#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>

#include "file.h"
#define DEBUG(s) fprintf(stderr, "%s", s);

File_info file_info;
static File_info array_of_file[NBFILE];
static int i = 0;

int fn(const char *fpath, const struct stat *sb, int tflag){


    if(tflag == FTW_F){
        file_info = set_file_info(sb->st_size, fpath);

        if(i < 10){
            
            array_of_file[i] = file_info;
            
    
            if(i > 1) sort_file_by_size(array_of_file, i+1);
            i++;
        }
        else{
            
            if(file_info.size > array_of_file[NBFILE - 1].size){
                array_of_file[NBFILE - 1] = file_info;
                sort_file_by_size(array_of_file, NBFILE);
            }

        }
    }

    return 0;
}

static void display_file_info(File_info files[]){
    int iteration;
    for(iteration = 0; iteration < i; iteration++){
        fprintf(stderr, "%s : %d octets\n", files[iteration].name, files[iteration].size);
    }
}

int main(int argc, char const *argv[])
{
    int flag = 0;
    
    ftw((argc < 2) ? "." : argv[1], fn, flag);

    display_file_info(array_of_file);
    return 0;
}
