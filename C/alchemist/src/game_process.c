#include "../includes/game_process.h"




static void exchange_bis(Board *board){
    switch(board->position){
        case 0: 
            if(board->right.coordinates.y < (ROW - 1)){
                hide_ball(board->right);
                board->right.coordinates.y = board->left.coordinates.y + 1;
                board->right.coordinates.x = board->left.coordinates.x;
            }
            break;
        case 1:
            
            hide_ball(board->right);
            board->right.coordinates.y = board->left.coordinates.y;
            board->right.coordinates.x = board->left.coordinates.x - 1;
            break;
        case 2:
            if(board->right.coordinates.y > 0){
                hide_ball(board->right);
                board->right.coordinates.y = board->left.coordinates.y - 1;
                board->right.coordinates.x = board->left.coordinates.x;
            }
            break;
        case 3:
            hide_ball(board->right);
            board->right.coordinates.y = board->left.coordinates.y;
            board->right.coordinates.x = board->left.coordinates.x + 1;
            break;
    }
}

void fall_vertical_left(Board *board){
    print_board(*board);
    while(!is_ball_submitted(*board, board->left) || !is_ball_submitted(*board, board->right)){
        
  
        board->boxes[board->left.coordinates.x][board->left.coordinates.y] = 0;
        hide_ball(board->left);
        board->left.coordinates.x += 1;
        board->boxes[board->left.coordinates.x][board->left.coordinates.y] = board->left.color;
        board->boxes[board->right.coordinates.x][board->right.coordinates.y] = 0;
        hide_ball(board->right);
        board->right.coordinates.x += 1;
        board->boxes[board->right.coordinates.x][board->right.coordinates.y] = board->right.color;


        draw_left_right(*board);

        MLV_wait_milliseconds(100);
    }
}

void render_exchange_balls(Board *board){
    board->position = (board->position + 1) % 4;
    exchange_bis(board);
    draw_left_right(*board);
}

void submit_and_draw_ball(Board *board, Ball ball){

}

void check_apply_gravity(Board *board, Container cont){
    int i;
    
    for(i = 0; i < cont->size; i++){
        while(!is_ball_submitted(*board, cont->array_ball[i])){
            board->boxes[cont->array_ball[i].coordinates.x][cont->array_ball[i].coordinates.y] = 0;
            hide_ball(cont->array_ball[i]);
            cont->array_ball[i].coordinates.x += 1;
            draw_ball(cont->array_ball[i]);
        }
        board->boxes[cont->array_ball[i].coordinates.x][cont->array_ball[i].coordinates.y] = cont->array_ball[i].color;
    }
    
    print_board(*board);
}

void erase_connexe_renderer(Board *board, Ball ball){
    Ball next;
    board->boxes[ball.coordinates.x][ball.coordinates.y] = EMPTY;
    hide_ball(ball);
    MLV_actualise_window();
    if(is_in_board(new_coordinates(ball.coordinates.x + 1, ball.coordinates.y)) &&
    (board->boxes[ball.coordinates.x + 1][ball.coordinates.y] == ball.color)){

        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x + 1, ball.coordinates.y);
        erase_connexe_renderer(board, next);
    }
    if(is_in_board(new_coordinates(ball.coordinates.x - 1, ball.coordinates.y)) &&
    (board->boxes[ball.coordinates.x - 1][ball.coordinates.y] == ball.color)){
        hide_ball(ball);
        MLV_actualise_window();
        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x - 1, ball.coordinates.y);
        erase_connexe_renderer(board, next);
    }
    if(is_in_board(new_coordinates(ball.coordinates.x, ball.coordinates.y + 1)) &&
    (board->boxes[ball.coordinates.x][ball.coordinates.y + 1] == ball.color)){
        hide_ball(ball);
        MLV_actualise_window();
        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x, ball.coordinates.y + 1);
        erase_connexe_renderer(board, next);
    }
    if(is_in_board(new_coordinates(ball.coordinates.x, ball.coordinates.y - 1)) &&
    (board->boxes[ball.coordinates.x][ball.coordinates.y - 1] == ball.color)){
        hide_ball(ball);
        MLV_actualise_window();
        next.color = ball.color;
        next.coordinates = new_coordinates(ball.coordinates.x, ball.coordinates.y - 1);
        erase_connexe_renderer(board, next);
    }
    return;
}

/** @brief After each phase */
int update_board_by_container(Board *board, Container cont)
{
    int updated = 0;
    int i;
    
    for(i = 0; i < cont->size; i++){
        if(is_connexity_applied(*board, cont->array_ball[i]))
        {
            hide_ball(cont->array_ball[i]);
            MLV_actualise_window();
            erase_connexe_renderer(board, cont->array_ball[i]);
        }
        while(!is_ball_submitted(*board, cont->array_ball[i]))
        {
            /*apply_gravity(board, &(cont->array_ball[i]));*/
            hide_ball(cont->array_ball[i]);
            MLV_actualise_window();
            cont->array_ball[i].coordinates.x++;
        }
    }
    
    for(i = cont->size; i >= 0; i--){
        if(remove_ball_if_empty_in_board(*board, cont, i))
        {
            updated = 1;
        }
    }
    return updated;
}

void action_play(Board *board, Container cont){

    while(!is_in_board(board->left.coordinates) && !is_in_board(board->right.coordinates)){
        hide_ball(board->left);
        hide_ball(board->right);
        board->left.coordinates.x += 1;
        board->right.coordinates.x += 1;
        draw_left_right(*board);
    }
    
    hide_ball(board->left);
    hide_ball(board->right);
    MLV_actualise_window();
    
    /* Make the objects falls until they are submit to gravity */
    while(!is_ball_submitted(*board, board->left) && !is_ball_submitted(*board, board->right)){
        hide_ball(board->left);
        hide_ball(board->right);
        board->left.coordinates.x += 1;
        board->right.coordinates.x += 1;
        draw_left_right(*board);
    }

    
    draw_left_right(*board);
    board->boxes[board->left.coordinates.x][board->left.coordinates.y] = board->left.color;
    board->boxes[board->right.coordinates.x][board->right.coordinates.y] = board->right.color;
    add_ball(cont, new_ball(board->left.coordinates, board->left.color));
    add_ball(cont, new_ball(board->right.coordinates, board->right.color));
    draw_board(cont);

    check_apply_gravity(board, cont);
    
    printf("CODE : %d\n", update_board_and_container(board, cont));
    redraw_board(*board);
}

void mv_balls_right(Board *board){


    if(board->right.coordinates.y < (ROW - 1) && board->left.coordinates.y < (ROW - 1)){
        hide_ball(board->left);
        hide_ball(board->right);
        board->left.coordinates.y += 1;
        board->right.coordinates.y += 1;
        draw_left_right(*board);
        MLV_actualise_window();
    }
    
    
}

void mv_balls_left(Board *board){


    if(board->left.coordinates.y > 0 && board->right.coordinates.y > 0){
        hide_ball(board->left);
        hide_ball(board->right);
        board->left.coordinates.y -= 1;
        board->right.coordinates.y -= 1;
        draw_left_right(*board);
        MLV_actualise_window();
    }
    
}