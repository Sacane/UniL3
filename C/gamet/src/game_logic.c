#include "../includes/game_logic.h"


void apply_gravity(Board *board, int x, int y){
    
}

int check_gravity_ok(Board board, int x, int y){
    return (x-1) >= 0 || board.boxes[x-1][y] > 0;
}


