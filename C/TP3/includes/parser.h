#ifndef __PARSER__H__
#define __PARSER__H__

#include "stdlib.h"
#include "opt.h"
#include <string.h>


#define OPERATOR 2
#define OPT 3
#define SPACES 4
#define ERROR 5

int is_numeric(char *input);
int parse_input(Stack *st, char *input, int *quit_opt);

#endif