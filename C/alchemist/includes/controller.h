#ifndef __CONTROLLER
#define __CONTROLLER

#include <MLV/MLV_all.h>
#include "board.h"
#include "game_process.h"

typedef enum {
    MV_RIGHT,
    MV_LEFT,
    MK_CHANGE,
    MK_FALL,
    UNDEFINED,
    QUIT,
}Operation;



Operation mlv_button_to_op(MLV_Keyboard_button button);

int make_operations(Board *board, Operation op, Container cont);

void move_balls_in_board(Board *board, Operation dir);



#endif