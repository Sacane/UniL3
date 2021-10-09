#ifndef __BOARD
#define __BOARD

#include "ball.h"
#include <assert.h>
#define ROW 6
#define COL 8

typedef struct board{


    int nb_color_unlocked; /* Number of unlocked colors */
    int boxes[COL][ROW];

}Board;

/* Set the boxes of the board to EMPTY */
void init_board(Board *board);

/* turn the board at his coordinate x y to the color representation */
void change_box_board(Board *board, JColor filled, int x, int y);

int check_limit(int x, int y);

#endif