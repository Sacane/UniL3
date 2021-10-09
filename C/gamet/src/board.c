#include "../includes/board.h"


void init_board(Board *board){
    int i, j;
    for(i = 0; i < COL; i++){
        for(j = 0; j < ROW; j++){
            board->boxes[i][j] = EMPTY;
        }
    }
}

void change_box_board(Board *board, JColor filled, int x, int y){
    assert(x <= COL);
    assert(y <= ROW);

    board->boxes[x][y] = filled;
}

int check_limit(int x, int y){
    return (x < COL && x >= 0) && (y < ROW && y >= 0);
}