#ifndef __BALL
#define __BALL

#include <assert.h>
#include <stdio.h>



#define ROW 6
#define COL 8

typedef enum {
    RIGHT,
    LEFT,
}Direction;

typedef enum {
    
    EMPTY,
    LIGHT_GREEN,
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

    int index;
    JColor color;
    Coordinates coordinates;

}Ball;



Ball init_ball(JColor color, int x, int y);
int is_in_board(Coordinates coordinate);
void print_coordinates(Coordinates coords);
void print_color(JColor color);
Coordinates new_coordinates(int x, int y);
int equals_ball(Ball b1, Ball b2);

#endif