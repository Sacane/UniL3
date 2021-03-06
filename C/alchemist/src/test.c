#include "../includes/test.h"



void test_board(){
    Board board;
    init_board(&board);

    print_board(board);

}

/*test non-updated
void test_gravity(){
    Board board;

    init_board(&board);
    print_board(board);


    printf("Test gravity :\n");
    board.boxes[COL - 1][5] = RED;
    board.boxes[0][5] = LIGHT_GREEN;
    print_board(board);

    printf("\n");
    apply_gravity(&board, 0, 5);
    print_board(board);
}*/

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

void test_border_connexe(){
    Board board;
    Ball NE, SE, NO, SO;

    NE.color = EMPTY;
    SE.color = EMPTY;
    NO.color = EMPTY;
    SO.color = EMPTY;

    NE.coordinates.x = 0;
    NE.coordinates.y = ROW - 1;

    SE.coordinates.x = COL - 1;
    SE.coordinates.y = ROW - 1;

    NO.coordinates.x = 0;
    NO.coordinates.y = 0;

    SO.coordinates.x = ROW - 1;
    SO.coordinates.y = 0;

    init_board(&board);

    printf("Connexity SO : %d\n", is_connexity_applied(board, SO));
    printf("Connexity NO : %d\n", is_connexity_applied(board, NO));
    printf("Connexity SE : %d\n", is_connexity_applied(board, SE));
    printf("Connexity NE : %d\n", is_connexity_applied(board, NE));


}

void test_erasing_connexe(){
    Board board;
    Ball ball;
    int score;
    ball.coordinates.x = 4;
    ball.coordinates.y = 3;
    ball.color = LIGHT_GREEN;
    Coordinates coords;
    init_board(&board);
    JColor jtest;
    board.boxes[4][4] = LIGHT_GREEN;
    board.boxes[4][5] = LIGHT_GREEN;
    board.boxes[4][3] = LIGHT_GREEN;
    board.boxes[5][3] = LIGHT_GREEN;

    print_board(board);
    
    printf("Connexity : %d\n", is_connexity_applied(board, ball));

    erase_connexe(&board, ball, &coords, &jtest, &score);


    print_board(board);
}

void test_turn_simulator(){
    Board board;
    int score;
    Container cont;
    cont = init_container(100);
    Ball b_test;
    b_test.coordinates.x = 7;
    b_test.coordinates.y = 0;
    b_test.color = LIGHT_GREEN;
    init_board(&board);
    init_turn(&board); /* Creates the 2 balls and put them into the board but not into the boxes */
    
    print_board(board);
    print_container(cont);
    /* Normally, between those instructions, the player has to control the balls */
    board.boxes[7][0] = 1; /* Test the case if the left/down react well to the gravity */
    set_left_right(&board);
    printf("After gravity applying : \n");
    print_board(board);
    
    add_ball(cont, board.left);
    add_ball(cont, board.right);
    add_ball(cont, b_test);
    printf("number of elements : %d\n", cont->size);
    printf("After adding balls\n");
    update_board_and_container(&board, cont, &score);
    printf("number of elements in container : %d\n", cont->size);
    printf("After one phase : \n");
    print_board(board);
    print_container(cont);
}

void test_window(){
    Board board;
    init_board(&board);
    MLV_Keyboard_button ev;
    MLV_create_window("Alchemist", "Alchemist", 700, 500);
    init_turn(&board);
    init_window(board);
    
    draw_left_right(board);

    MLV_wait_event(&ev, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    MLV_free_window();

}

void test_turn_simulator_img(){
    Board board;
    Container cont;
    cont = init_container(100);
    MLV_Keyboard_button ev;

    
    init_board(&board);
    init_turn(&board); /* Creates the 2 balls and put them into the board but not into the boxes */
    
    MLV_create_window("Alchemist", "Alchemist", 700, 500);
    init_window(board);

    draw_board(cont);
    draw_left_right(board);
    MLV_wait_event(&ev, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    
    hide_ball(board.left);
    hide_ball(board.right);

    MLV_actualise_window();

    MLV_wait_milliseconds(1000);

    draw_board(cont);
    MLV_free_window();
}

void test_controller(){
    Board board;
    Container cont;
    int score = 0;
    cont = init_container(100);
    MLV_Keyboard_button button;
    MLV_Button_state state;
    Operation op;
    int state_game;
    init_board(&board);
    init_turn(&board); /* Creates the 2 balls and put them into the board but not into the boxes */
    
    MLV_create_window("Alchemist", "Alchemist", 700, 500);
    init_window(board);
    draw_board(cont);
    draw_left_right(board);
    
    while(1){
        MLV_wait_event(&button, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
        op = mlv_button_to_op(button);
        if(state == MLV_RELEASED){
            continue;
        }
        if(state == MLV_PRESSED){
            state_game = make_operations(&board, op, cont, &score);
        }
        if(state_game == 0){
            break;
        }
        if(state_game == -1){
            init_turn(&board);
            draw_left_right(board);
        }

        draw_board(cont);
        
    }

    MLV_free_window();
}

