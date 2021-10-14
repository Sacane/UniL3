#ifndef __OPT__H__
#define __OPT__H__

#include "stack.h"
#include "operator.h"

#define ON_EXIT 0
#define ON_PROCESS 1





/**
 * @brief apply the severals options : 
 * -'a' to print all the value in the stack
 * -'p' to print only the head-value
 * -'c' to clear and free the stack 
 * -'r' to reverse the 2 firsts value in the stack
 * -'q' to quit the program
 * @param st stack which apply the function
 * @param input character to apply the options
 * @param quit_opt integer which can change if the option 'quit' is apply
*/
int opt_apply(Stack *st, char input, int *quit_opt);

#endif