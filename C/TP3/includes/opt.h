#ifndef __OPT__H__
#define __OPT__H__

#include "stack.h"
#include "operator.h"

#define ON_EXIT 0
#define ON_PROCESS 1






int opt_apply(Stack *st, char input, int *quit_opt);

#endif