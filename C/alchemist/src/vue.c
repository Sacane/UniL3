#include "../includes/vue.h"


static const int RADIUS = SIZE_CASE / 2;

static void draw_ball_in_board(int x, int y, MLV_Color mlv_color){
    MLV_draw_filled_circle((x * SIZE_CASE) + MARGIN_LEFT + (RADIUS), (y * SIZE_CASE) + MARGIN_TOP + (RADIUS), RADIUS, mlv_color);
}

static void hide_ball(Ball ball_to_hide){
    MLV_draw_filled_rectangle(ball_to_hide.coordinates.x, ball_to_hide.coordinates.y, SIZE_CASE, SIZE_CASE, MLV_COLOR_BLACK);
    MLV_actualise_window();
}

static MLV_Color jcolor_to_mlvcolor(JColor src){
    switch(src){
        case(LIGHT_GREEN): return MLV_COLOR_LIGHT_GREEN; 
        case(ORANGE): return MLV_COLOR_ORANGE;
        case(RED): return MLV_COLOR_RED;
        case(VIOLET): return MLV_COLOR_VIOLET;
        case(BLUE): return MLV_COLOR_BLUE;
        case(PASTEL_GREEN): return MLV_COLOR_GREEN2;
        case(SHADOW_GREEN): return MLV_COLOR_GREEN3;
        case(YELLOW): return MLV_COLOR_YELLOW;
        case(GREY): return MLV_COLOR_GREY;
        case(WHITE): return MLV_COLOR_WHITE;
        default: return MLV_COLOR_BLACK;

    }
}


void draw_left_right(Board board){
    draw_ball_in_board(board.left.coordinates.x, board.left.coordinates.y, jcolor_to_mlvcolor(board.left.color) );
    draw_ball_in_board(board.right.coordinates.x, board.right.coordinates.y, jcolor_to_mlvcolor(board.right.color) );
    printf("%d, %d\n", board.left.coordinates.x, board.left.coordinates.y);
    MLV_actualise_window();
}


void init_window(Board board)
{
    int i, j;
    MLV_draw_filled_rectangle(MARGIN_LEFT - DECALAGE, MARGIN_TOP - DECALAGE, WIN_X + (DECALAGE * 2), WIN_Y + (DECALAGE*2), MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(MARGIN_LEFT, MARGIN_TOP, WIN_X, WIN_Y, MLV_COLOR_BLACK);
    
    MLV_actualise_window();

}



