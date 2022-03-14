#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    printf("Bonjour\n");

    fork();

    printf("Au revoir\n");
    printf("2 times\n");
    return 0;
}
