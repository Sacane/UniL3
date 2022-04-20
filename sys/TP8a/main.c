#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "joblist.h"
#include "try.h"




#define CMD_ARGS(job) job->pipeline->head->args->array
#define CMD(job) job->pipeline->head->args->array[0]
#define JOB_PROC_HEAD(job) job->pipeline->head
#define PROCESS_CMD(proc) proc->args->array[0]
#define PROCESS_CMDLINE(proc) proc->args->array


#define PROMPT "$ "

static char *readCmdLine(void) {
  fprintf(stderr, "%s", PROMPT);
  char *result = NULL;
  size_t len = 0;
  if (getline(&result, &len, stdin) == -1) {
    fprintf(stderr, "\n");
    free(result);
    result = NULL;
  }
  else {
    len = strlen(result);
    if (len > 0 && result[len - 1] == '\n') {
      result[len - 1] = '\0';
    }
  }
  return result;
}

int buildtinCD(int argc, char **argv){
  if(argc < 2){
    //TODO
    return EXIT_SUCCESS;
  }
  try(chdir(argv[1]));
  return EXIT_SUCCESS;
}



void buildtinEXIT(int exit_status){
  
  exit(exit_status);

}

void child_process(
    int nextPipe[2], 
    int current_exit_value, 
    Proc *current_proc, 
    bool hasProcessRedirection, 
    bool isLastCMD
  ){
    int fd_in, fd_out;
    if(!strcmp("cd", current_proc->args->array[0]) || !(strcmp("exit", current_proc->args->array[0]))){
      exit(current_exit_value);
    }

    if(current_proc->redout){
      fd_out = try(open(
        current_proc->redout, 
        (current_proc->append) ? 
        O_CREAT | O_WRONLY | O_APPEND : 
        O_CREAT | O_WRONLY | O_TRUNC,
        S_IRUSR | S_IWUSR
      ));
      
      try(dup2(fd_out, STDOUT_FILENO));
      try(close(fd_out));
    }
    if(current_proc->redin){
      fd_in = try(open(
        current_proc->redin,
        O_RDONLY
      ));

      try(dup2(fd_in, STDIN_FILENO));
      try(close(fd_in));
    } 
    
    try(execvp(current_proc->args->array[0], current_proc->args->array));
}

void parent_process(Job *job, int *wstatus, int *ret_exit, Proc *process){
  if(!job->bg){
    try(wait(wstatus));
  }
  if(!(strcmp("cd", process->args->array[0]))){
    buildtinCD(process->args->size, process->args->array);
  }
  if(WIFSIGNALED(*wstatus)){
    *ret_exit = 128 + WTERMSIG(*wstatus);
  }
  if(WIFEXITED(*wstatus)){
    *ret_exit = WEXITSTATUS(*wstatus);
  }
  if(!strcmp("exit", process->args->array[0])){
    if(process->args->array[1]){
      *ret_exit = strtol(process->args->array[1], NULL, 10);
    }
    buildtinEXIT(*ret_exit);
  }
}



int main(void) {
  int wstatus;
  int ret_exit = 0;
  /* Pipe management */
  int i;
  int nextPipe[2];
  
  

  while (true) {
    i = 1;
    int prevPipe0;
    char *line = readCmdLine();
    if (!line) {
      break;
    }
    Job *job = newJobFromCmdLine(line);
    if(!strcmp("", line)){
      continue;
    }
    bool hasJobPipeline = (NULL != JOB_PROC_HEAD(job)->next);

    if (job) {
      /* Treat pipelines */
      for(Proc *process = job->pipeline->head; process; process = process->next){
        bool isFirstCmd = (i == 1);
        bool isLastCmd = (NULL == process->next);
        bool hasProcessRedirection = (NULL != process->redin || NULL != process->redout);

        if(hasJobPipeline && !isLastCmd){
          try(pipe(nextPipe));
        }
        switch(try(process->pid = fork())){
          case 0:
            if(!hasJobPipeline){
              child_process(nextPipe, ret_exit, process, hasProcessRedirection, isFirstCmd);
              break;
            }
            if(!isFirstCmd){
              try(dup2(prevPipe0, STDIN_FILENO));
              try(close(prevPipe0));
            }
            if(!isLastCmd){
              try(dup2(nextPipe[1], STDOUT_FILENO));
              try(close(nextPipe[0]));
              try(close(nextPipe[1]));
            }
            child_process(nextPipe, ret_exit, process, hasProcessRedirection, isFirstCmd);
            break;
          default:
            if(!hasJobPipeline){
              parent_process(job, &wstatus, &ret_exit, process);
              break;
            }
            if(!isLastCmd){
              try(close(nextPipe[1]));
              prevPipe0 = nextPipe[0];
            }
            parent_process(job, &wstatus, &ret_exit, process);
            break;
        }
        i++;
      }
      
      delJob(job);
    }

  }
  exit(EXIT_SUCCESS);
}
