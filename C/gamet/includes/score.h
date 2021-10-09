#ifndef __SCORE
#define __SCORE

#include "ball.h"

/*return the score value according to the color chosen */
int get_score_by_color(JColor color);

/* return the total score of the color chosen according to the number of balls connected */
int get_total_score(JColor color, int number);

#endif