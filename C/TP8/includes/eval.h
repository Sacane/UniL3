#ifndef __EVAL
#define __EVAL

#include "stack.h"
#include "operator.h"
#include "plugin.h"

/**
 * @brief change the stack to evaluate its values according to the operator, actually
 * this function can evaluate the following operators : '+', '-', '*', '/', '%', '^', '!'
 * @param st stack which contains the values to manipulate
 * @param operator to evaluate the stack
*/
int eval_operator(Stack *st, char operator);


/**
 * @brief Same function as eval_operator but the operation are loaded by plugins
 * 
 * @param st Stack which contains the values to calculate
 * @param plugins list of plugins used for the operations
 * @param operator operator as char to evaluate 
 * @return int 
 */
int eval_by_plugins(Stack *st, Plugin_list *plugins, char operator);
#endif