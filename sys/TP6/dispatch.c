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
    int pipe_out;
    int pipe_in;

}Process;

static Process co_processes[NP];

void set_processes(){
    int i;
    strcpy(co_processes[ADD].name, "./add");
    strcpy(co_processes[SUB].name, "./sub");
    strcpy(co_processes[MUL].name, "./mul");
    strcpy(co_processes[DIV].name, "./div");

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
    setbuf(stdout, NULL);
    char cmd[10];
    int n1, n2, res, n1_out, n2_out;
    int pIn[2], pOut[2];
    char buf[BUFSIZ];
    int i;
    int ret_scanf;
    set_processes();

    for(i = 0; i < NP; i++){
    
        try(pipe(pIn));
        try(pipe(pOut));

    
        switch(try(co_processes[i].pid = fork()) == 0){
        case 0:
            for (int j = 0; j < i; j++) { // Close pipes of previous children
                try(close(co_processes[j].pipe_in));
                try(close(co_processes[j].pipe_out));
            }
            try(dup2(pIn[READER], STDIN_FILENO));
            try(dup2(pOut[WRITER], STDOUT_FILENO));
            try(close(pIn[READER]));
            try(close(pIn[WRITER]));
            try(close(pOut[READER]));
            try(close(pOut[WRITER]));


            try(execvp(co_processes[i].name, argv));
        default: 
            try(close(pIn[0]));
            try(close(pOut[1]));
            co_processes[i].pipe_in = pIn[WRITER];
            co_processes[i].pipe_out = pOut[READER];
            break;
        } 
    }



    while(fgets(buf, sizeof(buf), stdin)){
        
        char *cmd = strtok(buf, " \t\n");
        if (!cmd) {
            cmd = "";
        }
        char *request = strtok(NULL, "");      // Remainder of string in buffer
        if (!request || !strchr(request, '\n')) {
            request = "\n";
        }
        if(!strcmp(cmd, "mul")){
            
            try(write(co_processes[MUL].pipe_in, request, strlen(request)));
            ssize_t len = try(read(co_processes[MUL].pipe_out, buf, sizeof(buf)));
            try(write(STDOUT_FILENO, buf, len));
            continue;
        }
        if(strcmp(cmd, "add") == 0){
                
            try(write(co_processes[ADD].pipe_in, buf, BUFSIZ));
            ssize_t len = try(read(co_processes[ADD].pipe_out, buf, BUFSIZ));
            try(write(STDOUT_FILENO, buf, len));
            continue;
        }
        
        if(strcmp(cmd, "sub") == 0){
            
            try(write(co_processes[SUB].pipe_in, buf, BUFSIZ));
            ssize_t len = try(read(co_processes[SUB].pipe_out, buf, BUFSIZ));
            try(write(STDOUT_FILENO, buf, len));
            continue;
        }
        
        if(strcmp(cmd, "div") == 0){
            
            try(write(co_processes[DIV].pipe_in, buf, BUFSIZ));
            ssize_t len = try(read(co_processes[DIV].pipe_out, buf, BUFSIZ));
            try(write(STDOUT_FILENO, buf, len));
            continue;
        }
        fflush(stdout);
    }

    





    return 0;
}
