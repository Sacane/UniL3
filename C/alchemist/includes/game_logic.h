#ifndef __GAME_LOGIC
#define __GAME_LOGIC

#include "board.h"
#include "container.h"

/* ======Gravity management====== */

int check_gravity_ok(Board board, int x, int y);

int is_coordinates_ok(int x, int y);

/* =======Connexe management======= */

int is_connexity_applied(Board board, Ball ball);

void init_turn(Board *board);

/**
 * @brief Set the ball at the left and right of the board, apply the gravity to them
*/
void set_left_right(Board *board);

int is_ball_submitted(Board board, Ball b);

void make_ball_left_right_falling(Board *board, Container cont);

int update_board_and_container(Board *board, Container cont);

void submit_balls(Board *board, Ball *ball);

#endif