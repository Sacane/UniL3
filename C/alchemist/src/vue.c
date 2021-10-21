#include "../includes/vue.h"


static const int RADIUS = SIZE_CASE / 2;

static void draw_ball_in_board(int x, int y, MLV_Color mlv_color){
    MLV_draw_filled_circle((x * SIZE_CASE) + MARGIN_LEFT + (RADIUS), (y * SIZE_CASE) + MARGIN_TOP + (RADIUS), RADIUS, mlv_color);
}

static void draw_left_right(Board board){
    draw_ball_in_board(board.left.coordinates.x, board.left.coordinates.y, board.left.color);
    draw_ball_in_board(board.right.coordinates.x, board.right.coordinates.y, board.right.color);
    MLV_actualise_window();
}


void init_window(Board board){
    int i, j;
    MLV_draw_filled_rectangle(MARGIN_LEFT - DECALAGE, MARGIN_TOP - DECALAGE, WIN_X + (DECALAGE*2), WIN_Y + (DECALAGE*2), MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(MARGIN_LEFT, MARGIN_TOP, WIN_X, WIN_Y, MLV_COLOR_BLACK);
    
    MLV_actualise_window();
    draw_left_right(board);

}