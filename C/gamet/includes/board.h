#ifndef __BOARD
#define __BOARD

#include "linkedlist.h"
#include <time.h>
#include <assert.h>
#include <stdlib.h>



#define VERTICAL 0
#define HORIZONTAL 1

typedef struct board{

    int nb_color_unlocked; /* Number of unlocked colors */
    int alignement; /* Alignement of the balls to choose */
    int boxes[COL][ROW];

}Board;

/* Set the boxes of the board to EMPTY */
void init_board(Board *board);

/* turn the board at his coordinate x y to the color representation */
void change_box_board(Board *board, JColor filled, int x, int y);

/* Check if the x and y is allow in the board */
int check_limit(int x, int y);

/* Select a random color according to the color unlocked in the board */
JColor rand_color(Board board);

int select_alignement(Board *board);

#endif