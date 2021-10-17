#include "../includes/game_logic.h"


void apply_gravity(Board *board, int x, int y){
    assert(x < COL);
    if(board->boxes[x + 1][y] != EMPTY){
        board->boxes[x + 1][y] = board->boxes[x][y];
        board->boxes[x][y] = EMPTY;
    }
}

int check_gravity_ok(Board board, int x, int y){
    return (x-1) >= 0 || board.boxes[x-1][y] > 0;
}

static int is_ball_connected_no(Board board, Ball ball){
    assert(ball.coordinates.x - 1 >= 0);
    assert(ball.coordinates.y - 1 >= 0);

    return (board.boxes[ball.coordinates.x - 1][ball.coordinates.y] == ball.color) &&
    (board.boxes[ball.coordinates.x][ball.coordinates.y - 1] == ball.color);
}

static int is_ball_connected_so(Board board, Ball ball){
    assert(ball.coordinates.x + 1 < COL);
    assert(ball.coordinates.y - 1 >= 0);

    return (board.boxes[ball.coordinates.x +1][ball.coordinates.y] == ball.color) &&
    (board.boxes[ball.coordinates.x][ball.coordinates.y - 1] == ball.color);    
}

static int is_ball_connected_ne(Board board, Ball ball){
    assert(ball.coordinates.x - 1 >= 0);
    assert(ball.coordinates.y + 1 < ROW);


    return (board.boxes[ball.coordinates.x +1][ball.coordinates.y] == ball.color) &&
    (board.boxes[ball.coordinates.x][ball.coordinates.y + 1] == ball.color); 
}
static int is_ball_connected_se(Board board, Ball ball){
    assert(ball.coordinates.x + 1 < COL);
    assert(ball.coordinates.y + 1 < ROW);


    return (board.boxes[ball.coordinates.x +1][ball.coordinates.y] == ball.color) &&
    (board.boxes[ball.coordinates.x][ball.coordinates.y + 1] == ball.color); 

}

static int is_ball_connected_ns(Board board, Ball ball){
    assert(ball.coordinates.x + 1 < COL);
    assert(ball.coordinates.x - 1 >= 0);


    return (board.boxes[ball.coordinates.x +1][ball.coordinates.y] == ball.color) &&
    (board.boxes[ball.coordinates.x - 1][ball.coordinates.y] == ball.color); 
}
static int is_ball_connected_eo(Board board, Ball ball){
    assert(ball.coordinates.y + 1 < ROW);
    assert(ball.coordinates.y - 1 >= 0);


    return (board.boxes[ball.coordinates.x][ball.coordinates.y + 1] == ball.color) &&
    (board.boxes[ball.coordinates.x][ball.coordinates.y - 1] == ball.color); 
}


int is_connexity(Board board, Ball ball){
    return 0;
}