#include <stdio.h>
#include <stdlib.h>

#include "../includes/test.h"
/*
1) Select random color for the two initial balls between the unlocked colors.
2) Attribute and create the two balls 
3) 

*/

int main(int argc, char const *argv[])
{
    /*test_board();
    test_gravity();*/
    
    test_connexity();
    printf("\n\n");
    test_erasing_connexe();
    test_container();
    return 0;
}
