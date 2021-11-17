  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

#ifndef __EVENTS__
#define __EVENTS__

#include <MLV/MLV_all.h>
#include "../plateau/plateau.h"
#include "../../graphics/plateau_drawer.h"

/*
* Cutom direction gesture
* All different methode convert all direction to this enum
*/
enum BKEY_Direction {
  BKEY_Direction_LEFT,
  BKEY_Direction_RIGHT,
  BKEY_Direction_UP,
  BKEY_Direction_DOWN,
  BKEY_Direction_NONE
};

/*
* Take the position of Empty_Box position
* And determinate if this direction to move can be taked
* If the direction was wrong change to BKEY_Direction_NONE
* If it's possible return the direction passed in props
*/
enum BKEY_Direction BKEY_valide_event(Empty_Box box, enum BKEY_Direction direction, int size);

/*
* Caclulate a random value and return randomly a direction
* < WARNING > the validity of movement not be checked
*/
enum BKEY_Direction BKEY_random_event();

/*
* Take a random event and check the validity of the movement
* return only if valide movement found
*/
enum BKEY_Direction BKEY_random_valide_event(Empty_Box box, int size);

/*
* Wait event return direction selected by user
* Return Keyboard direction or mouse direction
* < WARNING > the validity of movement not be checked
*/
enum BKEY_Direction BKEY_wait_event(Empty_Box box, int size);

/*
* Wait valide input by user
* return only if it's valide input
*/
enum BKEY_Direction BKEY_wait_valide_event(Panel panel, Empty_Box box);

/*
* Take keybard input and return Object type of struct BKEY_Direction
* Convert MLV_Keyboard_button to BKEY_Direction
*/
enum BKEY_Direction BKEY_keyboard_event(MLV_Keyboard_button user_keyboard);

/*
* Take mouse input and return Object type of struct BKEY_Direction
* (x,y) of mouse converted to a direction after compare
* to Empty_Box position
*/
enum BKEY_Direction BKEY_mouse_event(int x, int y, Empty_Box box, int size);

#endif
