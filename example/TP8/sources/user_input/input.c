#include "input.h"

int user_INPUT(char * input, int *boucle, Pile ** pile) {
  if (strlen(input) == 0) {               /* SAFE if user input is empty */
    fprintf(stderr, "\t[ Error < %s > not used ] \n", input);
    return -1;
  } else if (strlen(input) > 1) {         /* IF COMMANDE LENGHT > 2 NOT POSSIBLE */
    fprintf(stderr, "\t[ Error < %s > not used ] \n", input);
    return 1;
  } else {
    if ((*input) == 'q') {                /* QUIT REQUEST so stop main loop */
      (*boucle) = 0;                      /* Stop main with set boucle to 0 */
      return 1;
    } else if ((*input) == 'p') {         /* SHOW LAST VALUE IN PILE REQUEST */
      if ((*pile) == NULL) {
        fprintf(stderr, "\t[ Empty pile ]\n");
      } else {
        printf("%d\n", (*pile)->value);   /* Print last pile value */
      }
      return 1;
    } else if ((*input) == 'c') {         /* CLEAR ALL PILE REQUEST */
      free_PILE((*pile));                 /* Clear Pile */
      (*pile) = NULL;                     /* Set context pile to NULL */
      return 1;
    } else if ((*input) == 'a') {         /* PRINT ALL PILE REQUEST */
      if ((*pile) == NULL) {
        fprintf(stderr, "\t[ Empty pile ]\n");
      } else {
        print_PILE((*pile));              /* Print all pile */
      }
      return 1;
    } else if ((*input) == 'r') {         /* REVERSE REQUEST */
      if ((*pile) == NULL) {              /* Empty Pile */
        fprintf(stderr, "\t[ Empty pile ]\n");
        return -1;
      } else if ((*pile)->previous == NULL) { /* Previous Pile Empty to Reverse */
        fprintf(stderr, "\t[ No value to reverse ]\n");
        return -1;
      } else {                            /* Reverse Last 2 Pile */
        Pile * p = (*pile)->previous;
        (*pile)->previous = (*pile)->previous->previous;
        (*p).previous = (*pile);
        (*pile) = p;
        return 1;
      }
    }
  }
  return 0;                               /* ANY REQUEST EXECUTED SO RETURN 0 */
}
