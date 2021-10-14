#include "../includes/ball.h"

/*
return 1 if the coordinates are out of board, else where 0
*/
int check_out_of_board(Coordinates coordinate){
    return coordinate.y+1 > ROW || coordinate.y-1 < 0 || coordinate.x+1 >= COL || coordinate.x-1 <= 0;
}


Ball init_ball(JColor color, int x, int y){
    assert(x >= 0);
    assert(y >= 0);
    Ball ball;
    ball.coordinates.x = x;
    ball.coordinates.y = y;
    ball.color = color;
    return ball;
}

void b_move_right(Ball *ball){
    assert(check_out_of_board(ball->coordinates));
}
void b_move_left(Ball *ball){
    assert(check_out_of_board(ball->coordinates));
}
void b_move_north(Ball *ball){
    assert(check_out_of_board(ball->coordinates));
}
void b_move_south(Ball *ball){
    assert(check_out_of_board(ball->coordinates));


}