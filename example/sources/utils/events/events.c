  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

#include "events.h"

enum BKEY_Direction BKEY_valide_event(Empty_Box box, enum BKEY_Direction direction, int size) {
  if ((direction == BKEY_Direction_LEFT   && box->x == 0) ||
      (direction == BKEY_Direction_RIGHT  && box->x == size-1) ||
      (direction == BKEY_Direction_UP     && box->y == 0) ||
      (direction == BKEY_Direction_DOWN   && box->y == size-1)){
    /* If any invalid direction -> convert to BKEY_Direction_NONE to disable any move */
    return BKEY_Direction_NONE;
  }
  return direction;
}
/******************************************************************************/
enum BKEY_Direction BKEY_random_event() {
  /* The random number was generated with 1024 because between 0->3 its to much recursive */
  int random = MLV_get_random_integer(0,1024);
  return random%4; /* Reduce the random value */
}
/******************************************************************************/
enum BKEY_Direction BKEY_random_valide_event(Empty_Box box, int size) {
  enum BKEY_Direction direction = BKEY_random_event();
  if (BKEY_valide_event(box, direction, size) != BKEY_Direction_NONE) {
    /* Random direction was validated so return this direction */
    return direction;
  }
  /* Random generated direction was not valid so try a other Random */
  return BKEY_random_valide_event(box, size);
}
/******************************************************************************/
enum BKEY_Direction BKEY_wait_valide_event(Panel panel, Empty_Box box) {
  enum BKEY_Direction direction;
  do {
    /* Wait valide event */
    direction = BKEY_wait_event(box, panel->size);
  } while(BKEY_valide_event(box, direction, panel->size) == BKEY_Direction_NONE);
  return direction;
}
/******************************************************************************/
enum BKEY_Direction BKEY_wait_event(Empty_Box box, int size) {
  MLV_Keyboard_button user_keyboard;
  int user_mouse_x = -1; /* Init x_mouse to -1 (impossible value) */
  int user_mouse_y = -1; /* Init y_mouse to -1 (impossible value) */
  MLV_wait_keyboard_or_mouse(&user_keyboard, NULL, NULL, &user_mouse_x, &user_mouse_y);
  if (user_mouse_x < 0 && user_mouse_y < 0){
    /* If the value of mouse stay in impossible value it's not mouse event */
    return BKEY_keyboard_event(user_keyboard);
  }
  /* It's not mouse input so it's keybard event */
  return BKEY_mouse_event(user_mouse_x, user_mouse_y, box, size);
}
/******************************************************************************/
enum BKEY_Direction BKEY_keyboard_event(MLV_Keyboard_button user_keyboard) {
  /* Convert MLV_KEYBOARD value to personel enum BKEY_Direction */
  switch (user_keyboard) {
    case MLV_KEYBOARD_LEFT:
      return BKEY_Direction_LEFT;
    case MLV_KEYBOARD_RIGHT:
      return BKEY_Direction_RIGHT;
    case MLV_KEYBOARD_UP:
      return BKEY_Direction_UP;
    case MLV_KEYBOARD_DOWN:
      return BKEY_Direction_DOWN;
    default:
      return BKEY_Direction_NONE;
  }
}
/******************************************************************************/
enum BKEY_Direction BKEY_mouse_event(int x, int y, Empty_Box box, int size) {
  x = x / (PANEL_WIDTH / size); /* Convert mouse x value to get x_index */
  y = y / (PANEL_HEIGHT / size);/* Convert mouse y value to get y_index */
  if ((box->x)-1 == x && (box->y) == y)
    return BKEY_Direction_LEFT;
  if ((box->x)+1 == x && (box->y) == y)
    return BKEY_Direction_RIGHT;
  if ((box->x) == x && (box->y)-1 == y)
    return BKEY_Direction_UP;
  if ((box->x) == x && (box->y)+1 == y)
    return BKEY_Direction_DOWN;
  return BKEY_Direction_NONE; /* If any match founded */
}
