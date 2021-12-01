#ifndef __FILE
#define __FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NBFILE 10

typedef struct {
 
    int size;
    char name[FILENAME_MAX];

}File_info;


File_info set_file_info(int size, const char *name);

void sort_file_by_size(File_info files[], int number_of_element);

#endif