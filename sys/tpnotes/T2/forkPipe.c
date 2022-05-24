#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include "../try.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define WRITE_SIDE 1
#define READ_SIDE 0

//1) On manipule deux processus : (fork)
//2) Fils : On calcul une donnée (ici Datas)
//3) On veut faire communiquer cette donnée avec le processus père (pipe)
//4) On veut lire la donnée dans le processus père


typedef struct {
    int n;
    char c;
}Datas;

Datas data_init(){
    Datas d;
    d.c = 'c';
    d.n = 256;
    return d;
}

int main(int argc, char const *argv[])
{
    int n;
    Datas getter;
    int p[2];
    Datas d;


    try(pipe(p));

    switch(try(fork())){
        case 0:
            try(close(p[READ_SIDE]));
            d = data_init();
            try(write(p[WRITE_SIDE], &d, sizeof(Datas)));
            break;
        default:
            try(close(p[WRITE_SIDE]));
            try(wait(NULL));
            try(read(p[READ_SIDE], &getter, sizeof(Datas)));
            printf("n : %d\n", getter.n);
            printf("c : %c\n", getter.c);
            break;
    }
    return 0;
}
