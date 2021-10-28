#include "../includes/container.h"


Container init_container(int size){
    Container new_container;
    new_container = (Container)malloc(sizeof(Bag));
    new_container->max_length = INITSIZE;
    new_container->size = 0;
    new_container->array_ball = (Ball*) malloc(sizeof(Ball) * INITSIZE);
    if(!new_container->array_ball){
        fprintf(stderr, "Error allocation memory\n");
        exit(0);
    }

    return new_container;
}

void realloc_container(Container cont){
    (cont)->max_length *= 2;
    (cont)->array_ball = realloc((cont)->array_ball, sizeof(Ball) * cont->max_length);
    if(!(cont->array_ball)){
        fprintf(stderr, "Error reallocation memory\n");
        exit(0);
    }

}

void add_ball(Container cont, Ball ball){
    cont->array_ball[cont->size].color = ball.color;
    cont->array_ball[cont->size].coordinates.x = ball.coordinates.x;
    cont->array_ball[cont->size].coordinates.y = ball.coordinates.y;
    cont->size += 1;
    if(cont->size >= cont->max_length){
        realloc_container(cont);
    }
    
}

void clear_container(Container cont){
    free(cont->array_ball);
    free(cont);
}

void print_container(Container cont){
    int i;
    if(cont->size == 0){
        printf("Empty container\n");
        return;
    }
    for(i = 0; i < cont->size; i++){
        printf("Color of the ball : ");
        print_color(cont->array_ball[i].color);
        print_coordinates(cont->array_ball[i].coordinates);
    }
    printf("\n");
}

void remove_ball(Container cont, int index){
    
    if(cont->size >= 1)
        cont->array_ball[index] = cont->array_ball[(cont->size) - 1];
    cont->size--;
}