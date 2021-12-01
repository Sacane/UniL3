#include "file.h"
#define DEBUG(s) fprintf(stderr, "debugging")



File_info set_file_info(int size, const char *name){

    File_info file;

    strcpy(file.name, name);
    file.size = size;
    return file;

}


static int compare_file(const void *f1, const void *f2){
    File_info file_1 = *((File_info*)f1);
    File_info file_2 = *((File_info*)f2);
    
    return file_2.size - file_1.size;
}


void sort_file_by_size(File_info files[], int number_of_element){


    qsort(files, number_of_element, sizeof(File_info), compare_file);

}