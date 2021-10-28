#include "../includes/ball.h"

/*
return 1 if the coordinates are in the board, elsewhere 0
*/
int is_in_board(Coordinates coordinate){
    return coordinate.y < ROW && coordinate.y >= 0 && coordinate.x < COL && coordinate.x >= 0;
}

static int equals_coordinates(Coordinates c1, Coordinates c2){
    return (c1.x == c2.x) && (c1.y == c2.y);
}

int equals_ball(Ball b1, Ball b2){
    return (b1.color == b2.color) && 
    equals_coordinates(b1.coordinates, b2.coordinates);
}

Ball init_ball(JColor color, int x, int y){
    assert(x >= 0);
    assert(y >= 0);
    Ball ball;
    ball.coordinates.x = x;
    ball.coordinates.y = y;
    ball.color = color;
    return ball;
}

void print_coordinates(Coordinates coords){
    printf("Coordinates at : (%d, %d)\n", coords.x, coords.y);
}

void print_color(JColor color){
    switch(color){
        case EMPTY:
            printf("EMPTY\n");
            break;
        case LIGHT_GREEN:
            printf("Light green\n");
            break;
        case ORANGE:
            printf("Orange\n");
            break;
        case RED:
            printf("Red\n");
            break;
        case VIOLET:
            printf("Violet\n");
            break;
        case BLUE:
            printf("Blue\n");
            break;
        case PASTEL_GREEN:
            printf("Pastel green\n");
            break;
        case SHADOW_GREEN:
            printf("Shadow green\n");
            break;
        case YELLOW:
            printf("Yellow\n");
            break;
        case GREY:
            printf("Grey\n");
            break;
        case WHITE:
            printf("White\n");
            break;
        default:    
            fprintf(stderr, "W:Unknown color\n");
    }
}

Coordinates new_coordinates(int x, int y){
    Coordinates res;
    res.x = x;
    res.y = y;

    return res;
}

Ball new_ball(Coordinates coordinates, JColor color){
    Ball res;
    res.coordinates = coordinates;
    res.color = color;
    return res;
}