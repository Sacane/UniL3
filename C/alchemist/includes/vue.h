#ifndef __VUE
#define __VUE

#include "board.h"
#include "container.h"
#include <MLV/MLV_all.h>

#define WIN_Y 323
#define WIN_X 243
#define DECALAGE 5
#define SIZECASE 300
#define MARGIN_TOP 150
#define MARGIN_LEFT 100
#define WIDTH 512
#define HEIGHT 420
#define SIZE_CASE 40


void draw_ball(Ball ball);
void init_window(Board board);
void draw_left_right(Board board);
void draw_board(Container cont);
void hide_ball(Ball ball_to_hide);
void hide_left_right(Board board);
void redraw_board(Board board);






#endif