#include "../includes/controller.h"

void move_balls_in_board(Board *board, Operation dir)
{   
    if(dir == MV_LEFT){
        board->left.coordinates.y -= 1;
        board->right.coordinates.y -= 1;
    }
    if(dir == MV_RIGHT){
        board->right.coordinates.y += 1;
        board->left.coordinates.y += 1;
    }
}

static void mv_balls_right(Board *board){

    if(board->right.coordinates.y < (ROW - 1)){
        board->left.coordinates.y += 1;
        board->right.coordinates.y += 1;
    }
    
}

static void mv_balls_left(Board *board){


    if(board->left.coordinates.y > 0){
        board->left.coordinates.y -= 1;
        board->right.coordinates.y -= 1;
    }
    
}

static void change_alignement(Board *board){
    if(board->alignement == HORIZONTAL){
        board->alignement = VERTICAL;
    }
    else{
        board->alignement = HORIZONTAL;
    }
}


void make_operations(Board *board, Operation op){
    switch(op){
        case MV_LEFT:
            mv_balls_left(board);
            break;
        case MV_RIGHT:
            mv_balls_right(board);
            break;
        case MK_FALL:

            break;  
        case MK_CHANGE:
            change_alignement(board);
            break;
    }
}