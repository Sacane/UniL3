#include "../includes/opt.h"



static void opt_head(Stack st){
    printf("%ld\n", st->value);
}

static void opt_reverse_st(Stack *st){
    
    int tmp;
    
    tmp = (*st)->next->value;
    (*st)->next->value = (*st)->value;
    (*st)->value = tmp;
    
}



/* apply the options according to the input */
int opt_apply(Stack *st, char input, int *quit_opt){

    switch(input){
        case 'a': 
            if(st_length(*st) == 0){
                printf("W:empty stack\n");
                break;
            }
            st_print(*st);
            break;
        case 'p':
            if(st_length(*st) == 0){
                printf("W:empty stack\n");
                break;
            }
            opt_head(*st);
            break;
        case 'c':
            if(st_length(*st) == 0){
                printf("W:empty stack\n");
                break;
            }
            (*st) = st_clear(*st);
            break;
        case 'r':
            if(st_length(*st) < 2){
                printf("W:Not enough value in stack\n");
                break;
            }
            opt_reverse_st(st);
            break;
        case 'q':
            *quit_opt = ON_EXIT;
            break;
        default:
            return 0;
    }
    return 1;
}