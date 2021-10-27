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
    Ball left, right; /* The Two balls initialized at the beginning of the turn */
    int state_game_over; /* 0 if the board is completly filled, 1 if not */ 
    int is_falling;
    int boxes[COL][ROW]; /* Representation of the balls in the board */

}Board;

/* Set the boxes of the board to EMPTY */
void init_board(Board *board);

/* turn the board at his coordinate x y to the color representation */
void change_box_board(Board *board, JColor filled, int x, int y);

/* Select a random color according to the color unlocked in the board */
JColor rand_color(Board board);

void select_alignement(Board *board);

void print_board(Board board);

void erase_connexe(Board *board, Ball ball);


#endif