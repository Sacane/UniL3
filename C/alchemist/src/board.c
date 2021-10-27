#include "../includes/board.h"

void init_board(Board *board){
    int i, j;
    board->nb_color_unlocked = 1; /* Green Color unlocked */
    board->alignement = HORIZONTAL;
    board->state_game_over = 1;
    for(i = 0; i < COL; i++){
        for(j = 0; j < ROW; j++){
            board->boxes[i][j] = EMPTY;
        }
    }
}

void change_box_board(Board *board, JColor filled, int x, int y)
{
    assert(x < COL);
    assert(y < ROW);
    assert(x >= 0);
    assert(y >= 0);
    board->boxes[x][y] = filled;
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



void erase_connexe(Board *board, Ball ball){
    Ball next;
    board->boxes[ball.coordinates.x][ball.coordinates.y] = EMPTY;
    if(is_in_board(new_coordinates(ball.coordinates.x + 1, ball.coordinates.y)) &&
    (board->boxes[ball.coordinates.x + 1][ball.coordinates.y] == ball.color)){
        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x + 1, ball.coordinates.y);
        erase_connexe(board, next);
    }
    if(is_in_board(new_coordinates(ball.coordinates.x - 1, ball.coordinates.y)) &&
    (board->boxes[ball.coordinates.x - 1][ball.coordinates.y] == ball.color)){
        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x - 1, ball.coordinates.y);
        erase_connexe(board, next);
    }
    if(is_in_board(new_coordinates(ball.coordinates.x, ball.coordinates.y + 1)) &&
    (board->boxes[ball.coordinates.x][ball.coordinates.y + 1] == ball.color)){
        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x, ball.coordinates.y + 1);
        erase_connexe(board, next);
    }
    if(is_in_board(new_coordinates(ball.coordinates.x, ball.coordinates.y - 1)) &&
    (board->boxes[ball.coordinates.x][ball.coordinates.y - 1] == ball.color)){
        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x, ball.coordinates.y - 1);
        erase_connexe(board, next);
    }
    return;
}

/*
static void update_balls_left_and_right(Board *board){
    if(board->alignement == HORIZONTAL){
        if(board->left.coordinates.y != (COL - 1)){
            board->right.coordinates.x = board->left.coordinates.x;
            board->right.coordinates.y = board->left.coordinates.y + 1;
        }
    }
    else{
        board->right.coordinates.x = board->left.coordinates.x - 1;
        board->right.coordinates.y = board->left.coordinates.y;
    }
}
*/



