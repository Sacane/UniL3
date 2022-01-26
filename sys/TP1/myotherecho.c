#include "../try.h"
#include <fcntl.h>
#include <getopt.h>
#include <string.h>


int main(int argc, char *const *argv)
{   
    int i, start = 0;
    int j;
    int val;

    const char * optstring = "snS::";
    int isDesactivatedSeparator = 0;
    int isEOLDesactivated = 0;
    int isSuperSeparatorActivated = 0;
    char *separator = NULL;
    
    /* Getopt management for options */
    while(EOF != (val = getopt(argc, argv, optstring))){
        switch(val){
            case 's':
                start++;
                separator = "";
                isDesactivatedSeparator = 1;
                break;
            case 'n':
                start++;
                isEOLDesactivated = 1;
                break;
            case 'S':
                start+= 2;
                separator = malloc(sizeof(char*) * strlen(argv[2]));
                strcpy(separator, argv[2]);
                isSuperSeparatorActivated = 1;
                break;
            default:
                break;
        }
    }
    if(!isSuperSeparatorActivated && !isDesactivatedSeparator){
        separator = " ";
    }
    

    if(argc >= 2){
        for(i = 1 + start; i < argc; i++){
            write(1, argv[i], strlen(argv[i]));
            if(i < argc - 1){
                write(1, separator, strlen(separator));
            }
        }
        if(!isEOLDesactivated) write(1, "\n", 1);
        
    }
    
    if(isSuperSeparatorActivated) free(separator);
    
    return 0;
}
