#ifndef __PARSER__H__
#define __PARSER__H__

#include "stdlib.h"
#include "eval.h"
#include "opt.h"

#include <string.h>

#define DIGIT 1
#define OPERATOR 2
#define OPT 3
#define SPACES 4
#define ERROR 5


/**
@brief: check if the string is a number
@param: char* input 
@return: 1 if the string is a number, elsewhere return 0
*/
int is_numeric(char *input);

/**
 * @brief: Parse the input and apply the evaluation character by character.
 * @param st: pointer to a stack to update after manipulation of input
 * @param input: input to parse, according to its value return the character
 * @param quit_opt: pointer to an integer, put the value of ON_PROCESS or ON_EXIT if there is a "q" as token.
 * @return: return 1 if the parsing went well, 0 if not
*/
int parse(Stack *st, char *input, int *quit_opt, Plugin_list *plugins);

#endif