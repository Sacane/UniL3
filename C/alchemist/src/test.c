#include "../includes/test.h"



void test_board(){
    Board board;
    init_board(&board);

    print_board(board);

}

void test_gravity(){
    Board board;

    init_board(&board);
    print_board(board);


    /* Test gravity */
    printf("Test gravity :\n");
    board.boxes[COL - 1][5] = RED;
    board.boxes[0][5] = LIGHT_GREEN;
    print_board(board);

    printf("\n");
    apply_gravity(&board, 0, 5);
    print_board(board);
}

void test_connexity(){
    Board board;
    Ball ball;
    ball.coordinates.x = 4;
    ball.coordinates.y = 3;
    ball.color = LIGHT_GREEN;
    init_board(&board);

    board.boxes[4][4] = LIGHT_GREEN;
    board.boxes[4][5] = LIGHT_GREEN;
    board.boxes[4][3] = LIGHT_GREEN;
    board.boxes[5][3] = LIGHT_GREEN;

    print_board(board);

    printf("Connexity : %d\n", is_connexity_applied(board, ball));



}

void test_container(){
    Container cont;
    cont = init_container(100);

    Ball ball;
    ball.color = LIGHT_GREEN;
    ball.coordinates.x = 3;
    ball.coordinates.y = 4;
    add_ball(cont, ball);
    print_container(cont);
    clear_container(cont);
}

void test_erasing_connexe(){
    Board board;
    Ball ball;
    ball.coordinates.x = 4;
    ball.coordinates.y = 3;
    ball.color = LIGHT_GREEN;
    init_board(&board);

    board.boxes[4][4] = LIGHT_GREEN;
    board.boxes[4][5] = LIGHT_GREEN;
    board.boxes[4][3] = LIGHT_GREEN;
    board.boxes[5][3] = LIGHT_GREEN;

    print_board(board);

    printf("Connexity : %d\n", is_connexity_applied(board, ball));

    erase_connexe(&board, ball);


    print_board(board);
}