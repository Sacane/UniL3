#include "../includes/board.h"

void init_board(Board *board){
    int i, j;
    board->nb_color_unlocked = 1; /* Green Color unlocked */
    board->alignement = HORIZONTAL;
    for(i = 0; i < COL; i++){
        for(j = 0; j < ROW; j++){
            board->boxes[i][j] = EMPTY;
        }
    }
}

void change_box_board(Board *board, JColor filled, int x, int y){
    assert(x < COL);
    assert(y < ROW);
    assert(x >= 0);
    assert(y >= 0);
    board->boxes[x][y] = filled;
}


JColor rand_color(Board board){
    srand(time(NULL));
    return rand() % (board.nb_color_unlocked);
}

int select_alignement(Board *board){
    board->alignement = rand() % 2;
}



int apply_connexe(Board *board, LinkedList li){
    
}