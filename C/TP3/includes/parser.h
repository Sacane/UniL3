#ifndef __PARSER__H__
#define __PARSER__H__

#include "stdlib.h"
#include "opt.h"

#define NUMERIC 1
#define OPERATOR 2
#define OPT 3
#define ERROR 0

int is_numeric(char *input);
int parse_input(Stack *st, char *input);

#endif