#include "../includes/opt.h"


int main(int argc, char const *argv[])
{   
    Stack st;
    st = st_initialize();
    
    st = st_push(st, 10);
    st = st_push(st, 2);
    st = st_push(st, 1029);
    

    eval(&st, '+');
    st_print(st);
    opt_reverse_st(&st);
    st_print(st);
    st = st_clear(st);
    return 0;
}
