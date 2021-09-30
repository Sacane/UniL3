#ifndef __OPT__H__
#define __OPT__H__

#include "stack.h"
#include "operator.h"

void opt_head(Stack st);

void opt_free_st(Stack st);

void opt_print_st(Stack st);

Stack opt_reverse_st(Stack st);

int eval(Stack *st, char operator);

#endif