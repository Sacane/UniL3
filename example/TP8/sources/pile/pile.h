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
| Calculatos Pile Definition
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../plugin/plugin.h"

#ifndef __PILE__
#define __PILE__

/*
* Simple PILE architecture
* With :
*  - Previous pointure refere to previous Pile
*  - Value of the current pile
*/
typedef struct pile {
  struct pile *previous;
  int value;
} Pile;

/*
* Malloc function to malloc a Pile
* return NULL if malloc failled
*/
Pile * malloc_PILE(int value);


/*
* Add a Malloced pile in Pile
* If Malloc failled clear Pile and exit(-1)
*/
Pile * add_PILE(Pile * pile, int value);


/*
* Free all pile
* Start from the last file and free recursivly
*/
void free_PILE(Pile * pile);


/*
 * Modificate Pile state with take user input
 * modification affected from plugins
 * Return 0 -> if Modification failled
 * Return 1 -> if Modification succed
 *
 * Verison 2.0 create for plugins support
 */
int alter_PILE_from_plugin(Pile ** pile, BKEY_Plugin_List * plugins, char c);


/*
* Print all value in pile in Standard OUTPUT
* Recursive print
*/
void print_PILE(Pile * pile);


/*
* Test if have previous PILE
* Return 1 if previous pile not NULL
* Return 0 if previous pile NUll or current pile
* Show error message
*/
int previous_PILE_EXIST(Pile * pile);


/*
* Free the last PILE and return the previous PILE
* If previous PILE not exist free current Pile and return NULL
* Safe use if empty pile passed show error "Nothing to POP" and return NULL
*/
Pile * pop_PILE(Pile * pile);




#endif
