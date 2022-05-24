#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include "../../try.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define READE_SIDE 0
#define WRITE_SIDE 1

typedef enum {

    ADD,
    SUB,
    MUL,
    DIV

}NameProcess;

typedef struct {
    char cmd[6];
    int out;
    int in;
}Process;

Process process[4];

void set_processus(){
    strcpy(process[ADD].cmd, "./add");
    strcpy(process[MUL].cmd, "./mul");
    strcpy(process[DIV].cmd, "./div");
    strcpy(process[SUB].cmd, "./sub");

}



int main(int argc, char *const *argv)
{
    char buf[BUFSIZ];
    set_processus();
    int i;
    int pipeIn[2];
    int pipeOut[2];
    ssize_t len;


    for(i = 0; i < 4; i++){
        try(pipe(pipeIn));
        try(pipe(pipeOut));


        switch(try(fork())){
            case 0:
                try(dup2(pipeOut[WRITE_SIDE], STDOUT_FILENO));
                try(dup2(pipeIn[READE_SIDE], STDIN_FILENO));
                try(close(pipeIn[READE_SIDE]));
                try(close(pipeIn[WRITE_SIDE]));
                try(close(pipeOut[READE_SIDE]));
                try(close(pipeOut[WRITE_SIDE]));
                //TODO CLOSE
                try(execvp(process[i].cmd, argv));
                break;

            default:
                try(close(pipeIn[READE_SIDE]));
                try(close(pipeOut[WRITE_SIDE]));
                process[i].in = pipeIn[WRITE_SIDE];
                process[i].out = pipeOut[READE_SIDE];
                break;
        }
    }

    //add 8 7 
    //sub 10 2
    while(fgets(buf, sizeof(buf), stdin)){
        char *cmd = strtok(buf, " \t\n");
        char *newline = strtok(NULL, "");
        if(!cmd){
            cmd = "";
        }
        if(!newline || !strchr(newline, '\n')){
            newline = "\n";
        }
        if(strcmp(cmd, "mul") == 0){
            try(write(process[MUL].in, newline, strlen(newline)));
            len = try(read(process[MUL].out, buf, sizeof(buf)));
            try(write(STDOUT_FILENO, buf, len));
        }
        if(strcmp(cmd, "add") == 0){
            try(write(process[ADD].in, newline, strlen(newline)));
            len = try(read(process[ADD].out, buf, sizeof(buf)));
            try(write(STDOUT_FILENO, buf, len));
        }
        if(strcmp(cmd, "sub") == 0){
            try(write(process[SUB].in, newline, strlen(newline)));
            len = try(read(process[SUB].out, buf, sizeof(buf)));
            try(write(STDOUT_FILENO, buf, len));
        }
        if(strcmp(cmd, "div") == 0){
            try(write(process[DIV].in, newline, strlen(newline)));
            len = try(read(process[DIV].out, buf, sizeof(buf)));
            try(write(STDOUT_FILENO, buf, len));
        }
    }



    return 0;
}
