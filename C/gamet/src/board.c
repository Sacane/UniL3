#include "../includes/board.h"


void init_board(Board *board){
    int i, j;
    for(i = 0; i < COL; i++){
        for(j = 0; j < ROW; j++){
            board->boxes[i][j] = EMPTY;
        }
    }
}