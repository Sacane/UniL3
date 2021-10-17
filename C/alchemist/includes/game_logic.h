#ifndef __GAME_LOGIC
#define __GAME_LOGIC

#include "board.h"

/* ======Gravity management====== */

int check_gravity_ok(Board board, int x, int y);
void apply_gravity(Board *board, int x, int y);

int is_connexity(Board board, Ball ball);

#endif