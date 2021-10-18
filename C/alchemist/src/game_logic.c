#include "../includes/game_logic.h"


void apply_gravity(Board *board, int x, int y){
    assert(x < COL);
    if(board->boxes[x + 1][y] == EMPTY){
        board->boxes[x + 1][y] = board->boxes[x][y];
        board->boxes[x][y] = EMPTY;
    }
}

int is_coordinates_ok(int x, int y){
    return(x >= 0 && y >= 0 && x < COL && y < ROW);
}

static int is_ball_connected_no(Board board, Ball ball){

    return (is_coordinates_ok(ball.coordinates.x, ball.coordinates.y - 1)) && 
    (is_coordinates_ok(ball.coordinates.x - 1, ball.coordinates.y)) && 
    (board.boxes[ball.coordinates.x - 1][ball.coordinates.y] == ball.color) &&
    (board.boxes[ball.coordinates.x][ball.coordinates.y - 1] == ball.color);
}

static int is_ball_connected_so(Board board, Ball ball){


    return (is_coordinates_ok(ball.coordinates.x + 1, ball.coordinates.y)) && 
    (is_coordinates_ok(ball.coordinates.x, ball.coordinates.y - 1)) && 
    (board.boxes[ball.coordinates.x +1][ball.coordinates.y] == ball.color) &&
    (board.boxes[ball.coordinates.x][ball.coordinates.y - 1] == ball.color);    
}

static int is_ball_connected_ne(Board board, Ball ball){

    return (is_coordinates_ok(ball.coordinates.x - 1, ball.coordinates.y)) && 
    (is_coordinates_ok(ball.coordinates.x, ball.coordinates.y + 1)) && 
    (board.boxes[ball.coordinates.x - 1][ball.coordinates.y] == ball.color) &&
    (board.boxes[ball.coordinates.x][ball.coordinates.y + 1] == ball.color); 
}
static int is_ball_connected_se(Board board, Ball ball){

    return (is_coordinates_ok(ball.coordinates.x + 1, ball.coordinates.y)) &&
    (is_coordinates_ok(ball.coordinates.x, ball.coordinates.y + 1)) && 
    (board.boxes[ball.coordinates.x + 1][ball.coordinates.y] == ball.color) &&
    (board.boxes[ball.coordinates.x][ball.coordinates.y + 1] == ball.color); 

}

static int is_ball_connected_ns(Board board, Ball ball){

    return (is_coordinates_ok(ball.coordinates.x - 1, ball.coordinates.y)) && 
    (is_coordinates_ok(ball.coordinates.x + 1, ball.coordinates.y)) && 
    (board.boxes[ball.coordinates.x +1][ball.coordinates.y] == ball.color) &&
    (board.boxes[ball.coordinates.x - 1][ball.coordinates.y] == ball.color); 
}
static int is_ball_connected_eo(Board board, Ball ball){

    return (is_coordinates_ok(ball.coordinates.x, ball.coordinates.y - 1)) &&
    (is_coordinates_ok(ball.coordinates.x, ball.coordinates.y + 1)) && 
    (board.boxes[ball.coordinates.x][ball.coordinates.y + 1] == ball.color) &&
    (board.boxes[ball.coordinates.x][ball.coordinates.y - 1] == ball.color); 
}


int is_connexity_applied(Board board, Ball ball)
{
    return  (is_ball_connected_eo(board, ball)) ||
            (is_ball_connected_ne(board, ball)) ||
            (is_ball_connected_no(board, ball)) ||
            (is_ball_connected_ns(board, ball)) ||
            (is_ball_connected_so(board, ball)) ||
            (is_ball_connected_se(board, ball));
}

void parse_and_apply(Board *board, Container cont)
{
    Ball b1, b2;
    JColor color = rand_color(*board);
    b1.color = color;
    b2.color = color;
    add_ball(cont, b1);
    add_ball(cont, b2);
    board->alignement = HORIZONTAL;

}