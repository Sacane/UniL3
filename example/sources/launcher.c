  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

/*******************************************************************************
| Launcher file
| The project gesture file
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "utils/plateau/plateau.h"
#include "utils/events/events.h"
#include "utils/game_logic/game_logic.h"
#include "graphics/plateau_drawer.h"

int main(int argc, char const *argv[]) {
  /* Create all var necessary to play */
  Panel panel;
  Empty_Box box;
  int size = 4;                         /* Default size of game */
  char link[50] = "images/default.jpg"; /* Default taked image */
  int mixer = 120;                      /* Default complexity of Panel */

  int i;
  if (argc > 1) {                       /* If any option called on launch */
    for (i = 1; i < argc; i++){
      if (argv[i][0] == '-') {          /* Determinate if it's option */
        switch (argv[i][1]) {
          case 's':                     /* Option to change size of panel */
            size = (i+1 < argc) ? atoi(argv[i+1]) : 4;
            break;
          case 'm':                     /* Option to change complexity of panel */
            mixer = (i+1 < argc) ? atoi(argv[i+1]) : 120;
            break;
          case 'i':                     /* Option to change image */
            strcpy(link, ((i+1 < argc) ? argv[i+1] : link));
            break;
        }
      }
    }
  }

  panel = BKEY_init_GamePanel(size);    /* Init Panel with getted value */
  box = BKEY_init_Empty_Box(size);      /* Init Empty_Box with getted value */

  BKEY_window_gesture(1);
  BKEY_image_loader(panel, link);
  BKEY_draw_plateau(panel);
  BKEY_game_mixer(panel, box, mixer);
  BKEY_game_loop(panel, box);
  BKEY_draw_win_plateau(panel);
  BKEY_free_Game(panel, box);
  BKEY_window_gesture(0);
  return 0;
}
