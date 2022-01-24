#include "../try.h"
#include <fcntl.h>
#include <getopt.h>

int main(int argc, char const *argv[])
{   
    int i, begin = 0;

    int j;
    int val;

    const char * optstring = "snS::";
    int isDesactivatedSeparator = 0;
    int isEOLDesactivated = 0;

    while(EOF != (val = getopt(argc, argv, optstring))){
        switch(val){
            case 's':
                begin++;
                isDesactivatedSeparator = 1;
                break;
            case 'n':
                begin++;
                isEOLDesactivated = 1;
                break;
            case 'S':
                break;
            default:
                break;
        }
    }

    

    if(argc >= 2){
        for(i = 1 + begin; i < argc; i++){
            write(1, argv[i], strlen(argv[i]));
            if(i < argc - 1 && !isDesactivatedSeparator){
                write(1, " ", 1);
            }
        }
        if(!isEOLDesactivated) write(1, "\n", 1);
        
    }

    
    return 0;
}
