#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../try.h"
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>


#define READER 0
#define WRITER 1
#define PIP_CTX 2

#define NP 4

typedef enum {

    ADD, SUB, MUL, DIV

}Order;

typedef struct {

    char name[6];
    int pid;
    int pipe_out[2];
    int pipe_in[2];

}Process;

static Process co_processes[NP];

void set_processes(){
    int i;
    strcpy(co_processes[ADD].name, "./add");
    strcpy(co_processes[SUB].name, "./sub");
    strcpy(co_processes[MUL].name, "./mul");
    strcpy(co_processes[DIV].name, "./div");

    for(i = 0; i < NP; i++){
        try(pipe(co_processes[i].pipe_in));
        try(pipe(co_processes[i].pipe_out));
    }
}

int is_pid_ok(){
    int i;
    for (i = 0; i < NP; i++){
        if(co_processes[i].pid == 0){
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *const *argv)
{
    char cmd[10];
    int n1, n2, res, n1_out, n2_out;

    char buf[BUFSIZ];
    int i;

    set_processes();

    for(i = 0; i < NP; i++){
        if(try(co_processes[i].pid = fork()) == 0){

            try(close(co_processes[i].pipe_in[WRITER]));

            //On récupère les valeurs du père depuis le pipe reader
            try(read(co_processes[i].pipe_in[READER], &n1_out, sizeof(int)));
            try(read(co_processes[i].pipe_in[READER], &n2_out, sizeof(int)));
            
            //On redirige la sortie en lecture du pipe_out pour insérer le resultat du programme dedans
            try(dup2(co_processes[i].pipe_out[WRITER], STDIN_FILENO));
            try(dup2(co_processes[i].pipe_out[READER], STDOUT_FILENO));

            //On envoi les valeurs dans le pipe_out 
            try(write(co_processes[i].pipe_out[WRITER], &n1_out, sizeof(int)));
            try(write(co_processes[i].pipe_out[WRITER], &n2_out, sizeof(int)));
            try(execvp(co_processes[i].name, argv));
            
        }
    }


    if(is_pid_ok()){
        while(1){
            scanf("%s %d %d", cmd, &n1, &n2);
            if(!strcmp(cmd, "mul")){
                try(close(co_processes[MUL].pipe_in[READER]));
                try(close(co_processes[MUL].pipe_out[WRITER]));
                
                try(write(co_processes[MUL].pipe_in[WRITER], &n1, sizeof(int)));
                try(write(co_processes[MUL].pipe_in[WRITER], &n2, sizeof(int)));
                


                //On lit le resultat depuis le pipe
                try(read(co_processes[MUL].pipe_out[READER], &res, sizeof(int)));
                printf("res : %d\n", res);


            }
            
            if(strcmp(cmd, "add") == 0){
                
                //TODO
                printf("%d\n", res);
            }
            
            if(strcmp(cmd, "sub") == 0){
                
                //TODO
                printf("%d\n", res);
            }
            
            if(strcmp(cmd, "div") == 0){
                
                //TODO
                printf("%d\n", res);
            }
        }

    }





    return 0;
}
