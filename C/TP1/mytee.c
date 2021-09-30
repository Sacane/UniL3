#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

int main(int argc, char** argv){
    char c;

    FILE *f = fopen(argv[1], "w");
    if(f == NULL){
        printf("Erreur lors de l'ouverture du fichier ! \n");
        exit(0);
    }
    
    while((c = getchar()) != EOF){
        putchar(c);
        fputc(c, f);
    }
    fclose(f);
    return 0;
}