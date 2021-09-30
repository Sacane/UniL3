#include "../includes/stack.h"

Stack st_initialize(){
    return NULL;
}

int is_st_empty(Stack st){
    return (st == NULL);
}

Stack st_push(Stack st, int value){
    Stack tmp;
    tmp = (Stack)malloc(sizeof(St));
    if(tmp == NULL){
        fprintf(stderr, "Error during allocation of the stack\n");
        exit(1);
    }

    tmp->value = abs(value);
    tmp->next = st;
    return tmp;
}

Stack st_pop(Stack st){
    Stack tmp = NULL;
    if(is_st_empty(st)){
        return NULL;
    }
    tmp = st->next;
    free(st);
    return tmp;
}

Stack st_clear(Stack st){
    while(!(is_st_empty(st))){
        st = st_pop(st);
    }
    return st_initialize();
}

int st_length(Stack st){
    int res;
    Stack tmp;
    tmp = st;
    res = 0;

    while(tmp != NULL){
        res++;
        tmp = tmp->next;
    }
    return res;
}

void st_print(Stack st){
    Stack tmp;
    tmp = st;
    while(!(is_st_empty(tmp))){
        printf("%d\n", tmp->value);
        tmp = tmp->next;
    }
}