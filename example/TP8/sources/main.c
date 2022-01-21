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
| Entery point of Calculatos
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "pile/pile.h"
#include "user_input/input.h"
#include "pluginsLoader/pluginsLoader.h"

int main(int argc, char const *argv[]) {

  int boucle = 1;                         /* Main while controller */
  char *input;                            /* User input manager variable */
  long ret;                               /* User input number */
  char *ptr;                              /* User input char */
  Pile * pile = NULL;                     /* Initialise NULL Pile */
  BKEY_Plugin_List * plugins;             /* Init plugins list */


  printf("Auto-loading of plugins..\n");
  plugins = BKEY_plugin_loader();         /* Auto loading all disponible plugin */

  while (boucle) {
    input = readline(NULL);               /* Readline user input */
    add_history(input);

    input = strtok(input, " ");           /* Split user input */
    while (input != NULL) {               /* While to test all word in line */
      ret = strtol(input, &ptr, 10);      /* strtol module return int if exist and change ptr if exist*/
      if (*ptr == '\0') {                 /* ptr empty so it's a number */
        pile = add_PILE(pile, (int)ret);  /* Add the value in PILE */
      } else {
                                          /* Custom user request */
        if (user_INPUT(ptr, &boucle, &pile) == 0) {
          alter_PILE_from_plugin(&pile, plugins ,ptr[0]);
        }
      }
      input = strtok(NULL, " ");          /* GO TO NEXT VALUE */
    }
  }
  free_PILE(pile);                        /* Free all Pile before safe exit */
  BKEY_free_plugin_list(plugins);         /* Free all plugin malloced */
  return 0;                               /* Safe exit main */
}
