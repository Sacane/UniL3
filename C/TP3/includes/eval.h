#ifndef __EVAL
#define __EVAL

#include "stack.h"
#include "operator.h"

/**
 * @brief change the stack to evaluate its values according to the operator, actually
 * this function can evaluate the following operators : '+', '-', '*', '/', '%', '^', '!'
 * @param st stack which contains the values to manipulate
 * @param operator to evaluate the stack
*/
int eval(Stack *st, char operator);


#endif