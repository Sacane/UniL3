  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

/******************************************************************************
| TP 8 Prog - C
| Calculatos Input module
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../pile/pile.h"

#ifndef __INPUT__
#define __INPUT__

/*
 * Get word passed in line by user and make somthing
 * Return 0  -> Nothing made
 * Return 1  -> Request succedfuly executed
 * Return -1 -> Request cant be executed
 *
 * Props
 * char input -> User input
 * int * boucle -> main controller
 * Pile * pile -> state PILE
 */
int user_INPUT(char * input, int *boucle, Pile ** pile);

#endif
