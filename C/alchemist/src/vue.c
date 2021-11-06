#include "../includes/vue.h"


static const int RADIUS = SIZE_CASE / 2;

static void draw_ball_in_board(int x, int y, MLV_Color mlv_color){
    MLV_draw_filled_circle((x * SIZE_CASE) + MARGIN_LEFT + (RADIUS), (y * SIZE_CASE) + MARGIN_TOP + (RADIUS), RADIUS, mlv_color);
}

void hide_ball(Ball ball_to_hide){
    draw_ball_in_board(ball_to_hide.coordinates.y, ball_to_hide.coordinates.x, MLV_COLOR_BLACK);
    
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

void redraw_board(Board board){
    int i, j;
    
    for(i = 0; i < COL; i++){
        for(j = 0; j < ROW; j++){
            draw_ball_in_board(j, i, jcolor_to_mlvcolor(board.boxes[i][j]));
        }
    }
    MLV_actualise_window();
}



void draw_left_right(Board board){
    draw_ball_in_board(board.left.coordinates.y, board.left.coordinates.x, jcolor_to_mlvcolor(board.left.color) );
    draw_ball_in_board(board.right.coordinates.y, board.right.coordinates.x, jcolor_to_mlvcolor(board.right.color) );
    MLV_actualise_window();
}
void hide_left_right(Board board){
    draw_ball_in_board(board.left.coordinates.y, board.left.coordinates.x, MLV_COLOR_BLACK);
    draw_ball_in_board(board.right.coordinates.y, board.right.coordinates.x, MLV_COLOR_BLACK);
    MLV_actualise_window();
}

void draw_ball(Ball ball){
    draw_ball_in_board(ball.coordinates.y, ball.coordinates.x, jcolor_to_mlvcolor(ball.color));
    MLV_actualise_window();
}

void draw_board(Container cont)
{
    int i;
    for(i = 0; i < cont->size; i++){
        draw_ball(cont->array_ball[i]);
    }
    MLV_actualise_window();
}

void init_window(Board board)
{
    MLV_draw_filled_rectangle(MARGIN_LEFT - DECALAGE, MARGIN_TOP - DECALAGE, WIN_X + (DECALAGE * 2), WIN_Y + (DECALAGE*2), MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle(MARGIN_LEFT, MARGIN_TOP, WIN_X, WIN_Y, MLV_COLOR_BLACK);
    draw_score(0);
    MLV_actualise_window();

}

void draw_unlocked_colors(){
    
}

