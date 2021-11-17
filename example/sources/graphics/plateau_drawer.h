  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

#ifndef __GAMEPANEL__
#define __GAMEPANEL__

#define PANEL_WIDTH   600
#define PANEL_HEIGHT  600

#include <MLV/MLV_all.h>
#include "../utils/plateau/plateau.h"

/*
* Windows gesture
* option : 0 -> Close and free window
* option : 1 -> Init open windows
*/
void BKEY_window_gesture(int option);

/*
* Image loader, take panel and link
* Load image from link into panel->image
* < WARNING > wrong link or failled load exit()
*/
void BKEY_image_loader(Panel panel, char *link);

/*
* Main plateau drawer
* Take a plateau and draw him
*/
void BKEY_draw_plateau(Panel panel);

/*
* Take a specific area in image and draw at index
* Index represent the place of box in game
*/
void BKEY_draw_partial_image(Panel panel, int index);

/*
* Draw empty case at index position
*/
void BKEY_draw_empty_box(Panel panel, int index);

/*
* Animation when user finish the puzzle
* Draw all case and finish with drawing original image
*/
void BKEY_draw_win_plateau(Panel panel);

#endif
