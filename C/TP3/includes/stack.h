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
 * @brief Initialize a new stack to NULL, use it just for more visibility in your code.
 * @return the stack initialized to NULL
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

/**
 * @brief check if the stack is empty or not
 * @param st stack to check
 * @return 1 if the stack is empty, elsewhere return 0
*/
int st_is_empty(Stack st);

/**
 * @brief clear the head of the stack, the stack following the head becomes the head itself.
 * @return the new stack with its head poped.
 * @param st stack to remove the head.
*/
Stack st_pop(Stack st);

/**
 * @brief classic counting of the length of the stack in O(n)
 * @param st stack to count the length
 * @return the length of the stack
*/
int st_length(Stack st);

/**
 * @brief classic print of the stack 
 * @param st stack to print the elements
*/
void st_print(Stack st);

#endif