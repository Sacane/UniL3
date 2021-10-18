#ifndef __CONTAINER
#define __CONTAINER

#include "ball.h"
#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100

typedef struct {
    int max_length;
    int size;
    Ball *array_ball;

}Bag, *Container;


Container init_container(int size);

void add_ball(Container cont, Ball ball);

void realloc_container(Container cont);

void clear_container(Container cont);

void print_container(Container cont);

void remove_ball(Container cont, int index);

#endif