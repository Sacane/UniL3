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


int make_operations(Board *board, Operation op){
    switch(op){
        case MV_LEFT:
            fprintf(stderr, "move left");
            mv_balls_left(board);
            break;
        case MV_RIGHT:
            fprintf(stderr, "move right");
            mv_balls_right(board);
            break;
        case MK_FALL:
            fprintf(stderr, "make fall\n");
            break;  
        case MK_CHANGE:
            fprintf(stderr, "Alignement changed\n");
            change_alignement(board);
            break;
        case UNDEFINED:
            fprintf(stderr, "Undefined operation");
            break;
        case QUIT:
            fprintf(stderr, "Quit");
            return 0;
    }
    return 1;
}

Operation mlv_button_to_op(MLV_Keyboard_button button){
    switch(button){

        case MLV_KEYBOARD_d: return MV_RIGHT;
            
        case MLV_KEYBOARD_q: return MV_LEFT;
            
        case MLV_KEYBOARD_z: return MK_CHANGE;
            
        case MLV_KEYBOARD_s: return MK_FALL;

        case MLV_KEYBOARD_ESCAPE: return QUIT;
            
        default: return UNDEFINED; 
            
    }
}