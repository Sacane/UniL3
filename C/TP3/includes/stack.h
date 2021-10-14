#ifndef __STACK__H__
#define __STACK__H__


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct St{

    long value;
    struct St *next;

}St, *Stack;

/**
 * @brief Initialize a new stack to NULL;
 */ 
Stack st_initialize();

/**
 * @brief create a new stack and push the value which become the first element of the new stack, the old one is the next stack of the new one.
 * @param st stack 
 * @param value to push 
 * @return the new Stack after pushed
*/
Stack st_push(Stack st, long value);

/**
 * @brief clear and free all the cell of the given stack
 * @return the stack cleared
*/
Stack st_clear(Stack st);

int st_is_empty(Stack st);

Stack st_pop(Stack st);

int st_length(Stack st);

void st_print(Stack st);

#endif