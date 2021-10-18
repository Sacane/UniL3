#ifndef __BOARD
#define __BOARD

#include "ball.h"
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define VERTICAL 1
#define HORIZONTAL 2

typedef struct board{

    int nb_color_unlocked; /* Number of unlocked colors */
    int alignement; /* Alignement of the balls to choose it could take the value : VERTICAL or HORIZONTAL*/
    int boxes[COL][ROW]; 

}Board;

/* Set the boxes of the board to EMPTY */
void init_board(Board *board);

/* turn the board at his coordinate x y to the color representation */
void change_box_board(Board *board, JColor filled, int x, int y);

/* Select a random color according to the color unlocked in the board */
JColor rand_color(Board board);

void select_alignement(Board *board);


void print_board(Board board);

#endif