#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "joblist.h"
#include "try.h"


#define CMD(job) job->pipeline->head->args->array[0]

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

int main(void) {
  while (true) {
    char *line = readCmdLine();
    if (!line) {
      break;
    }
    Job *job = newJobFromCmdLine(line);
    if (job) {
      // TODO: Do something more useful with the job!
      switch(try(job->id = fork())){
        case 0:
          if(!(strcmp("cd", CMD(job)))){
            buildtinCD(job->pipeline->head->args->size, job->pipeline->head->args->array);
          } else {
            try(execvp(CMD(job), job->pipeline->head->args->array));
          }
          break;
        default:
          if(!job->bg){
            try(wait(NULL));
          }

          break;
      }


      delJob(job);
    }
  }
  exit(EXIT_SUCCESS);
}
