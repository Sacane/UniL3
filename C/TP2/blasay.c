#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 80
#define DIVSPACES 4

void print_space(int start, int end){
    int i;
    for(i = start; i <= end; i++){
        printf(" ");
    }
}

void printMessageAscii(const char s[]){

    int i, count = 0;
    int size = strlen(s);

    /* top */
    printf("--");
    for(i = 0; i < size; i++){
        printf("-");
        if(i == MAX){
            break;
        }
    }
    printf("--\n");

    /* message */
    i = 0;
    while(s[i] != '\0'){
        printf("%c", s[i]);
        if(i % MAX == 0 && i != 0){
            printf("\n");
        }
        i++;
    }
    printf("\n");
    /* Bottom */
    printf("-");
    for(i = 0; i < size; i++){
        printf("-");
        if(i == MAX){
            break;
        }
    }
    printf("---\n");
    print_space(0, size/DIVSPACES);
    printf("\\ \n");
    print_space(0, size/DIVSPACES);
    printf(" \\ \n");
    print_space(0, size/DIVSPACES);
    printf("  \\ \n");
    print_space(0, size/DIVSPACES);
    printf("   \\ \n");
}

void voitureAscii(int size){
    print_space(0, size/DIVSPACES);
    printf("           ------------------\n");
    print_space(0, size/DIVSPACES);
    printf("   .--H--.|c'est pas sorcier |\n");
    print_space(0, size/DIVSPACES);
    printf(" _//_||  ||                  |\n");
    print_space(0, size/DIVSPACES);
    printf("[    -|  |'--;---------------'\n");
    print_space(0, size/DIVSPACES);
    printf("'-()-()----()'()^^^^^^^()()'");
    printf("\n");

}


int main(int argc, char const *argv[])
{   

    int size;
    if(argc < 2){
        fprintf(stderr, "You have to put a string as argument\n");
        exit(1);
    }

    size = strlen(argv[1]);
    printMessageAscii(argv[1]);
    voitureAscii(size);
    return 0;
}
