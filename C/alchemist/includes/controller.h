#ifndef __CONTROLLER
#define __CONTROLLER

#include <MLV/MLV_all.h>

#include "board.h"

typedef enum {
    MV_RIGHT,
    MV_LEFT,
    MK_CHANGE,
    MK_FALL,
}Operation;

void make_operations(Board *board, Operation op);

void move_balls_in_board(Board *board, Operation dir);



#endif