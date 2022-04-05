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

    for(i = 0; i < 4; i++){
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
    int ret_scanf;
    set_processes();

    for(i = 0; i < NP; i++){
        if(try(co_processes[i].pid = fork()) == 0){
            

            try(dup2(co_processes[i].pipe_in[READER], STDIN_FILENO));
            try(dup2(co_processes[i].pipe_out[WRITER], STDOUT_FILENO));

            try(close(co_processes[i].pipe_out[READER]));
            try(close(co_processes[i].pipe_in[WRITER]));
            
            try(close(co_processes[i].pipe_out[WRITER]));
            try(close(co_processes[i].pipe_in[READER]));

            try(execvp(co_processes[i].name, argv));

        } else {
            try(close(co_processes[i].pipe_out[WRITER]));
            try(close(co_processes[i].pipe_in[READER]));
        }
    }


    if(is_pid_ok()){
        while(1){
            if((ret_scanf = scanf("%s %d %d", cmd, &n1, &n2)) != 3){
                fprintf(stderr, "Not found 3 elements, instead : %d\n", ret_scanf);
                exit(EXIT_FAILURE);
            }

            

            if(!strcmp(cmd, "mul")){

                sprintf(buf, "%d %d", n1, n2);
                try(write(co_processes[MUL].pipe_in[WRITER], buf, BUFSIZ));
                try(read(co_processes[MUL].pipe_out[READER], buf, BUFSIZ));
                printf("res : %s", buf);

            }
            
            if(strcmp(cmd, "add") == 0){
                 sprintf(buf, "%d %d", n1, n2);
                try(write(co_processes[ADD].pipe_in[WRITER], buf, BUFSIZ));
                try(read(co_processes[ADD].pipe_out[READER], buf, BUFSIZ));
                printf("res : %s", buf);
            }
            
            if(strcmp(cmd, "sub") == 0){
                sprintf(buf, "%d %d", n1, n2);
                try(write(co_processes[SUB].pipe_in[WRITER], buf, BUFSIZ));
                try(read(co_processes[SUB].pipe_out[READER], buf, BUFSIZ));
                printf("res : %s", buf);
            }
            
            if(strcmp(cmd, "div") == 0){
                sprintf(buf, "%d %d", n1, n2);
                try(write(co_processes[DIV].pipe_in[WRITER], buf, BUFSIZ));
                try(read(co_processes[DIV].pipe_out[READER], buf, BUFSIZ));
                printf("res : %s", buf);
            }
            
        }

    }





    return 0;
}
