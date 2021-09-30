#include <stdio.h>
#include <stdlib.h>

#define N 100

char c_glob = '\0';
char c_glob2 = '\n';
static char sc_glob = 'c';

int main(int argc, char const *argv[])
{  
    static char sc_loc = 'p';
    char loc1 = 'a';
    char loc2 = 'i';

    char *dyn1 = (char*)malloc(sizeof(char) * N);
    char *dyn2 = (char*)malloc(sizeof(char) * N);
    

    printf("static <--> globale : %ld\n", (&sc_glob - &c_glob));
    printf("static <--> local1 : %ld\n", (&sc_loc - &loc1));
    printf("static <--> local2 : %ld\n", (&sc_glob - &loc2));
    printf("static local <--> allouée1 : %ld\n", (&sc_loc - dyn1));
    printf("static <--> allouée2 : %ld\n", (&sc_glob - dyn2));
    printf("globale <--> local1 : %ld\n", (&c_glob - &loc2));
    printf("globale2 <--> local2 : %ld\n", (&c_glob2 - &loc2));
    printf("local1 <--> allouée1 : %ld\n", (&loc1 - dyn1));

    free(dyn1);
    free(dyn2);


    return 0;
}
