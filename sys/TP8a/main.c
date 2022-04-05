#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "joblist.h"
#include "try.h"

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

int main(void) {
  while (true) {
    char *line = readCmdLine();
    if (!line) {
      break;
    }
    Job *job = newJobFromCmdLine(line);
    if (job) {
      // TODO: Do something more useful with the job!
      printJob(job);
      delJob(job);
    }
  }
  exit(EXIT_SUCCESS);
}
