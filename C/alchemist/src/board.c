#include "../includes/board.h"

void upgrade_position(Board *board){
    board->position = (board->position + 1) % 4;
}

void init_board(Board *board){
    int i, j;
    board->nb_color_unlocked = 1; /* Green Color unlocked */
    board->alignement = HORIZONTAL;
    board->state_game_over = 1;
    board->position = 0;
    for(i = 0; i < COL; i++){
        for(j = 0; j < ROW; j++){
            board->boxes[i][j] = EMPTY;
        }
    }
}


JColor rand_color(Board board)
{
    srand(time(NULL));
    printf("Color unlocked : %d\n", board.nb_color_unlocked);
    return rand() % (board.nb_color_unlocked);
}

void select_alignement(Board *board){
    board->alignement = rand() % 2;
}

void print_board(Board board){
    int i, j;
    for(i = 0; i < COL; i++){
        for(j = 0; j < ROW; j++){
            printf("[%d] ", board.boxes[i][j]);
        }
        printf("\n");
    }
}




