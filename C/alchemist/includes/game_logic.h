#ifndef __GAME_LOGIC
#define __GAME_LOGIC

#include "board.h"
#include "container.h"


/* ======Gravity management====== */

int check_gravity_ok(Board board, int x, int y);
void apply_gravity(Board *board, int x, int y);

int is_coordinates_ok(int x, int y);

/* =======Connexe management======= */

int is_connexity_applied(Board board, Ball ball);

void parse_and_apply(Board *board, Container cont);

#endif