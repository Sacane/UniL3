#ifndef __BALL
#define __BALL

#define EMPTY 0

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


typedef struct{

    JColor color;
    
}Ball;






#endif