#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_space(int start, int end){
    int i;
    for(i = start; i <= end; i++){
        printf(" ");
    }
}

void printMessageAscii(const char s[]){

    int i;
    int size = strlen(s);

    /* top */
    printf("--");
    for(i = 0; i < size; i++){
        printf("-");
    }
    printf("--\n");

    /* message */
    printf("< %s >\n", s);

    /* Bottom */
    printf("-");
    for(i = 0; i < size; i++){
        printf("-");
    }
    printf("---\n");
    print_space(0, size/2);
    printf("\\ \n");
    print_space(0, size/2);
    printf(" \\ \n");
    print_space(0, size/2);
    printf("  \\ \n");
    print_space(0, size/2);
    printf("   \\ \n");
}

void voitureAscii(int size){
    print_space(0, size/2);
    printf("           ------------------\n");
    print_space(0, size/2);
    printf("   .--H--.|c'est pas sorcier |\n");
    print_space(0, size/2);
    printf(" _//_||  ||                  |\n");
    print_space(0, size/2);
    printf("[    -|  |'--;---------------'\n");
    print_space(0, size/2);
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
