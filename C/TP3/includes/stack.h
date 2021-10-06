#ifndef __STACK__H__
#define __STACK__H__


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct St{

    long value;
    struct St *next;

}St, *Stack;

Stack st_initialize();

Stack st_push(Stack st, long value);

Stack st_clear(Stack st);

int st_is_empty(Stack st);

Stack st_pop(Stack st);

int st_length(Stack st);

void st_print(Stack st);

#endif