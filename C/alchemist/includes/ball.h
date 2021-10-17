#ifndef __BALL
#define __BALL

#include <assert.h>


#define EMPTY 0

#define ROW 6
#define COL 8

typedef enum {
    
    
    LIGHT_GREEN = 1,
    ORANGE,
    RED,
    VIOLET,
    BLUE,
    PASTEL_GREEN,
    SHADOW_GREEN,
    YELLOW,
    GREY,
    WHITE
    
}JColor;

typedef struct {
    
    int x;
    int y;

}Coordinates;

typedef struct {

    JColor color;
    Coordinates coordinates;

}Ball;



Ball init_ball(JColor color, int x, int y);
int check_out_of_board(Coordinates coordinate);
void b_move_right(Ball *ball);
void b_move_left(Ball *ball);
void b_move_north(Ball *ball);
void b_move_south(Ball *ball);


#endif