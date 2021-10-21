#include <stdio.h>
#include <stdlib.h>

#include "../includes/test.h"
/*
==== STATE 1 ====
- Create 2 balls according to the unlocked colors
- Let the user control the balls until he type "bottom" or "d"

==== STATE 2 ====
- Apply the gravity of the 2 balls

==== STATE 3 ====
-Check if the falled balls has a connexity with the others and erase them.
-Check if there still are balls floating in the board

*/

int main(int argc, char const *argv[])
{
    /*test_board();
    test_gravity();*/
    
    /*test_connexity();
    printf("\n\n");
    test_erasing_connexe();
    test_container();
    test_border_connexe();*/

    test_turn_simulator();
    return 0;
}
