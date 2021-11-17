  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

#ifndef __LOGIC__
#define __LOGIC__

#include <MLV/MLV_all.h>
#include "../events/events.h"
#include "../plateau/plateau.h"
#include "../../graphics/plateau_drawer.h"

/*
* GameLoop of game
* < WARNING > only wave to exit this loop it's to win
*/
void BKEY_game_loop(Panel panel, Empty_Box box);

/*
* BKEY_game_mixer, take panel and change the position of case
* to prepare the gamePanel to be playable
* Int mixer -> number of time how the panel was mixed
* Bigger was mixer bigger was the difficulty to resolve game
*/
void BKEY_game_mixer(Panel panel, Empty_Box box, int mixer);

/*
* This mixer logic
* Take a last direction how made, to disable the opposite direction
* It's to block make inutile move like UP and after DOWN to assure the mixity of Panel
*/
enum BKEY_Direction BKEY_mixer_logic(enum BKEY_Direction last_dir, Empty_Box box, int size);

/*
* Take a direction and assure the changement of the Empty_Box position
* Determinate value for BKEY_move_call
*/
void BKEY_move(Panel panel, Empty_Box box , enum BKEY_Direction direction);

/*
* Get Empty_Box and the information about next position to call BKEY_switch_box
* Change value of box how was the information about the Empty_Box
*/
void BKEY_move_call(Panel panel, Empty_Box box, int dx, int dy);

/*
* Function how determinate if all Box was on good position
* return 0 -> min 1 element was not on this good place
* return 1 -> all Box was on good place
*/
int BKEY_isWin(Panel panel);

#endif
