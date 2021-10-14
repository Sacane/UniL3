#include "../includes/eval.h"

static long is_binary_op(char operator){
    switch (operator){
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
            return 1;
            break;
        case '!':
            return 0;
            break;
        default:
            return -1;
    }
}

int st_check(Stack st, char operator){
    if(is_binary_op(operator)){
        if(st_is_empty(st) || !(st->next)){
            fprintf(stdout, "W:Not enough value in the stack\n");
            return 0;
        }
    }
    else{
        if(st_is_empty(st)){
            fprintf(stdout, "W:Empty stack\n");
            return 0;
        }
    }
    return 1;
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
            if((*st)->next->value == 0){
                fprintf(stderr, "W:Divide by 0\n");
                break;
            }
            eval = divide((*st)->value, (*st)->next->value);
            st_binary_update(&(*st), eval);
            break;
        case '^':
            eval = expo((*st)->next->value, (*st)->value);
            st_binary_update(&(*st), eval);
            break;
        case '!':
            if((*st)->value == 0){
                fprintf(stderr, "W:fact by 0\n");
                break;
            }
            eval = fact((*st)->value);
            st_unary_update(&(*st), eval);
            break;
        case '%':
            if((*st)->next->value == 0){
                fprintf(stderr, "W:Divide by 0\n");
                break;
            }
            eval = mod((*st)->value, (*st)->next->value);
            st_binary_update(&(*st), eval);
            break;
        default:
            return;
    }
}

int eval(Stack *st, char operator){

    if(!st_check(*st, operator)){
        return 0;
    }

    st_update(&(*st), operator);
    return 1;
}
