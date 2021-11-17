  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

#include "game_logic.h"

void BKEY_game_loop(Panel panel, Empty_Box box) {
  /* < WARNING > only wave to quit this loop it's to win */
  while (BKEY_isWin(panel) == 0) {
    /* Call move with valid move */
    BKEY_move(panel, box, BKEY_wait_valide_event(panel, box));
    /* Draw the new panel */
    BKEY_draw_plateau(panel);
  }
}
/******************************************************************************/
void BKEY_game_mixer(Panel panel, Empty_Box box, int mixer) {
  int i;
  enum BKEY_Direction direction_tmp = BKEY_Direction_NONE;
  MLV_wait_milliseconds(300); /* Wait before mixer start */
  for (i = 0; i < mixer; i++) {
    /* Pass direction to mixer logic to determinate good direction */
    direction_tmp = BKEY_mixer_logic(direction_tmp, box, panel->size);
    BKEY_move(panel, box, direction_tmp);
    BKEY_draw_plateau(panel);
    MLV_wait_milliseconds(30); /* Wait a lite to make litle animation */
    i++;
  }
}
/******************************************************************************/
enum BKEY_Direction BKEY_mixer_logic(enum BKEY_Direction last_dir, Empty_Box box, int size) {
  enum BKEY_Direction current_dir = BKEY_random_valide_event(box, size);
  if ((last_dir == BKEY_Direction_LEFT && current_dir == BKEY_Direction_RIGHT) ||
      (last_dir == BKEY_Direction_RIGHT && current_dir == BKEY_Direction_LEFT) ||
      (last_dir == BKEY_Direction_UP && current_dir == BKEY_Direction_DOWN) ||
      (last_dir == BKEY_Direction_DOWN && current_dir == BKEY_Direction_UP)) {
    /* If the current_dir kill the previouse direction change to other direction */
    return BKEY_mixer_logic(last_dir, box, size);
  }
  return current_dir;
}
/******************************************************************************/
int BKEY_isWin(Panel panel) {
  int index;
  for (index = 0; index < panel->size*panel->size; index++) {
    if (((panel->panel[index].y * panel->size) + panel->panel[index].x) != index)
      return 0;
  }
  return 1;
}
/******************************************************************************/
void BKEY_move(Panel panel, Empty_Box box , enum BKEY_Direction direction) {
  if (direction == BKEY_Direction_LEFT)
    BKEY_move_call(panel, box, -1, 0);
  if (direction == BKEY_Direction_RIGHT)
    BKEY_move_call(panel, box, +1, 0);
  if (direction == BKEY_Direction_UP)
    BKEY_move_call(panel, box, 0, -1);
  if (direction == BKEY_Direction_DOWN)
    BKEY_move_call(panel, box, 0, +1);
}
/******************************************************************************/
void BKEY_move_call(Panel panel, Empty_Box box, int dx, int dy) {
  BKEY_switch_box(&panel->panel[(box->y * panel->size) + box->x ], &panel->panel[((box->y+dy) * panel->size) + (box->x+dx)]);
  /* Change value of Empty_Box tracker with new positon */
  box->x += dx;
  box->y += dy;
}
