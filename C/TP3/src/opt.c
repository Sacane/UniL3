#include "../includes/opt.h"


void opt_head(Stack st){
    printf("%d\n", st->value);
}

void opt_reverse_st(Stack *st){
    
    int tmp;
    
    tmp = (*st)->next->value;
    (*st)->next->value = (*st)->value;
    (*st)->value = tmp;
    
}

static void st_binary_update(Stack *st, int value){
    *st = st_pop(*st);
    *st = st_pop(*st);
    *st = st_push(*st, value);
}

static void st_unary_update(Stack *st, int value){
    *st = st_pop(*st);
    *st = st_push(*st, value);
}


static void st_update(Stack *st, char operator){
    int eval;
    switch(operator){
        case '+':
            eval = sum((*st)->value, (*st)->next->value);
            st_binary_update(&(*st), eval);
            break;
        case '-':
            eval = sub((*st)->value, (*st)->next->value);
            st_binary_update(&(*st), eval);
            break;
        case '*':
            eval = mul((*st)->value, (*st)->next->value);
            st_binary_update(&(*st), eval);
            break;
        case '/':
            eval = divide((*st)->value, (*st)->next->value);
            st_binary_update(&(*st), eval);
            break;
        case '^':
            eval = expo((*st)->value, (*st)->next->value);
            st_binary_update(&(*st), eval);
            break;
        case '!':
            eval = fact((*st)->value);
            st_unary_update(&(*st), eval);
            break;
        default:
            return;
    }
}

int eval(Stack *st, char operator){
    int length;
    length = st_length((*st));
    if(is_binary_op(operator)){
        if(length < 2){
            return 0;
        }
    }else{
        if(st_is_empty((*st))){
            return 0;
        }
    }

    st_update(&(*st), operator);
    return 1;
}

/* apply the options according to the input */
int opt_apply(Stack *st, char input){

    switch(input){
        case 'a':
            st_print(*st);
            break;
        case 'p':
            printf("%d\n", (*st)->value);
            break;
        case 'c':
            (*st) = st_clear(*st);
            break;
        case 'r':
            opt_reverse_st(st);
            break;
        default:
            return 0;
    }
    return -1;
}