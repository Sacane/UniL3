#include "../includes/game_logic.h"


static void apply_gravity(Board *board, Ball *b)
{
    fprintf(stderr, "test\n");
    /* If we're in the boxes, update the board's one */
    if(b->coordinates.x >= 0 && board->boxes[b->coordinates.x + 1][b->coordinates.y] == EMPTY){
        board->boxes[b->coordinates.x + 1][b->coordinates.y] = board->boxes[b->coordinates.x][b->coordinates.y];
        board->boxes[b->coordinates.x][b->coordinates.y] = EMPTY;
    }
    b->coordinates.x += 1; /* Update the Row of the ball */
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

void init_turn(Board *board)
{

    Ball b1, b2;
    Coordinates left, right;
    JColor color_left = MLV_get_random_integer(1, board->nb_color_unlocked); 
    JColor color_right = MLV_get_random_integer(1, board->nb_color_unlocked);
    
    left.x = -2;
    left.y = 0;
    right.x = -2;
    right.y = 1;
    b1.color = color_left;
    b2.color = color_right;
    b1.coordinates = left;
    b2.coordinates = right;
    board->alignement = HORIZONTAL;
    board->left = b1;
    board->right = b2;

}


int remove_ball_if_empty_in_board(Board board, Container cont, int index){
    int state = 0;
    if(board.boxes[cont->array_ball[index].coordinates.x][cont->array_ball[index].coordinates.y] != cont->array_ball[index].color){
        remove_ball(cont, index);
        state = 1;
    }
    return state;
}

int is_ball_submitted(Board board, Ball b)
{
    /* There is 2 conditions : 1) the ball is at the full bottom of the board
                               2) the ball is standing on another ball
    */
    
    if(b.coordinates.x + 1 >= COL){
        return 1;
    }
    if(board.boxes[b.coordinates.x + 1][b.coordinates.y] != EMPTY){
        return 1;
    }
    return 0;
}

static int is_connexity_into_container(Board *board, Container cont){
    int i;
    for(i = 0; i < cont->size; i++){
        if(is_connexity_applied(*board, cont->array_ball[i]) || !is_ball_submitted(*board, cont->array_ball[i]))
        {
            return 1;
        }
    }
    return 0;
}

/** @brief After each phase */
int update_board_and_container(Board *board, Container cont)
{
    int updated = 0, score = 0;
    int i;
    Coordinates coords;
    JColor jcolor;
    Ball ball_spawned;
    while(is_connexity_into_container(board, cont)){
        for(i = 0; i < cont->size; i++){
            if(is_connexity_applied(*board, cont->array_ball[i]))
            {
                
                erase_connexe(board, cont->array_ball[i], &coords, &jcolor, &score);
                if(jcolor > board->nb_color_unlocked){
                    board->nb_color_unlocked = jcolor;
                }
                printf("COORDINATES : %d, %d\n", coords.x, coords.y);
                ball_spawned = new_ball(coords, jcolor);
                board->boxes[coords.x][coords.y] = jcolor;
                add_ball(cont, ball_spawned);
            }
            if(!is_ball_submitted(*board, cont->array_ball[i]))
            {
                updated = 1;
                apply_gravity(board, &(cont->array_ball[i]));
            }
        }
    }

    
    for(i = cont->size - 1; i >= 0; i--){
        print_container(cont);
        remove_ball_if_empty_in_board(*board, cont, i);
        
    }
    return updated;
}

void submit_balls(Board *board, Ball *ball){
    while(!is_ball_submitted(*board, *ball)){
        ball->coordinates.x += 1;
    }
    board->boxes[ball->coordinates.x][ball->coordinates.y] = ball->color;
}

void set_left_right(Board *board){
    while(!is_in_board(board->left.coordinates) && !is_in_board(board->right.coordinates)){
        board->left.coordinates.x += 1;
        board->right.coordinates.x += 1;
    }

    while(1){
        
        if(!is_ball_submitted(*board, board->left)){
            board->left.coordinates.x += 1;
        }
        if(!is_ball_submitted(*board, board->right)){
            board->right.coordinates.x += 1;
        }

        if(is_ball_submitted(*board, board->left) && is_ball_submitted(*board, board->right))
            break;
    }
    board->boxes[board->left.coordinates.x][board->left.coordinates.y] = board->left.color;
    board->boxes[board->right.coordinates.x][board->right.coordinates.y] = board->left.color;
}



void erase_connexe(Board *board, Ball ball, Coordinates *newCoordinates, JColor *jcolor, int *score){
    Ball next;
    int check_bottom, check_left;
    board->boxes[ball.coordinates.x][ball.coordinates.y] = EMPTY;
    *score += get_score_by_color(ball.color);
    if(is_in_board(new_coordinates(ball.coordinates.x + 1, ball.coordinates.y)) &&
    (board->boxes[ball.coordinates.x + 1][ball.coordinates.y] == ball.color)){
        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x + 1, ball.coordinates.y);
        erase_connexe(board, next, newCoordinates, jcolor, score);
        check_bottom = 0;
    }else{
        check_bottom = 1;
    }
    
    if(is_in_board(new_coordinates(ball.coordinates.x - 1, ball.coordinates.y)) &&
    (board->boxes[ball.coordinates.x - 1][ball.coordinates.y] == ball.color)){
        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x - 1, ball.coordinates.y);
        erase_connexe(board, next, newCoordinates, jcolor, score);
    }
    if(is_in_board(new_coordinates(ball.coordinates.x, ball.coordinates.y + 1)) &&
    (board->boxes[ball.coordinates.x][ball.coordinates.y + 1] == ball.color)){
        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x, ball.coordinates.y + 1);
        erase_connexe(board, next, newCoordinates, jcolor, score);
    }
    if(is_in_board(new_coordinates(ball.coordinates.x, ball.coordinates.y - 1)) &&
    (board->boxes[ball.coordinates.x][ball.coordinates.y - 1] == ball.color)){
        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x, ball.coordinates.y - 1);
        erase_connexe(board, next, newCoordinates, jcolor, score);
        check_left = 0;
    }
    else{
        check_left = 1;
    }
    if(check_left && check_bottom){
        *newCoordinates = ball.coordinates;
        *jcolor = ball.color + 1;
    }
    return;
}
