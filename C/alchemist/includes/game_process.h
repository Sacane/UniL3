#ifndef __GAME_PROCESS
#define __GAME_PROCESS


#include <MLV/MLV_all.h>

#include "vue.h"
#include "game_logic.h"


void action_play(Board *board, Container cont);

void mv_balls_right(Board *board);

void mv_balls_left(Board *board);

void render_exchange_balls(Board *board);
#endif