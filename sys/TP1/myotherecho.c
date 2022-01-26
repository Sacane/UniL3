#include "../try.h"
#include <fcntl.h>
#include <getopt.h>
#include <string.h>


int main(int argc, char *const *argv)
{   
    int i;
    int j;
    int val;

    const char * optstring = "snS:";
    int isDesactivatedSeparator = 0;
    int isEOLDesactivated = 0;
    int isSuperSeparatorActivated = 0;
    char *separator = " ";
    
    /* Getopt management for options */
    while(EOF != (val = getopt(argc, argv, optstring))){
        switch(val){
            case 's':

                separator = "";
                isDesactivatedSeparator = 1;
                break;
            case 'n':

                isEOLDesactivated = 1;
                break;
            case 'S':

                isSuperSeparatorActivated = 1;
                break;
            default:
                break;
        }
    }


    if(argc >= 2){
        for(i = optind; i < argc; i++){
            write(1, argv[i], strlen(argv[i]));
            if(i < argc - 1){
                if(isSuperSeparatorActivated){
                    write(1, argv[2], strlen(argv[2]));
                }
                else
                {
                    write(1, separator, strlen(separator));
                }
                
                
            }
        }
        if(!isEOLDesactivated) write(1, "\n", 1);
        
    }
    

    
    return 0;
}
