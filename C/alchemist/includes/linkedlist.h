#ifndef __LINKEDLIST
#define __LINKEDLIST

#include "ball.h"

typedef struct cell{

    Ball ball;

    struct cell *next;

}LinkedList, *Cell;


Cell new_linkedList();

Cell li_add(Cell list, int value);

Cell li_clear(Cell list);



#endif