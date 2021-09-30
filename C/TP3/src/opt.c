#include "../includes/opt.h"


void opt_head(Stack st){
    printf("%d\n", st->value);
}

void opt_free_st(Stack st);
void opt_print_st(Stack st);

Stack opt_reverse_st(Stack st){
    Stack tmp;
    int this, next;

    this = st->value;
    next = st->next->value;

    tmp = st_pop(tmp);
    tmp = st_pop(tmp);

    tmp = st_push(tmp, this);
    tmp = st_push(tmp, next);
    
    return tmp;
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
            printf("ici\n");
            eval = sum((*st)->value, (*st)->next->value);
            st_binary_update(&(*st), eval);
            printf("after : %d\n", (*st)->value);
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
            eval = expo((*st)->value);
            st_unary_update(&(*st), eval);
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
        if(is_st_empty((*st))){
            return 0;
        }
    }

    st_update(&(*st), operator);
    printf("%d\n", (*st)->value);
    return 1;
}
