#include "../includes/operator.h"

int is_binary_op(char operator){
    switch (operator){
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            return 1;
            break;
        case '!':
        case '^':
            return 0;
            break;
        default:
            return -1;
    }
}


int sum(int a, int b){
    return a + b;
}

int sub(int a, int b){
    return a - b;
}

int divide(int a, int b){
    return a / b;
}

int mul(int a, int b){
    return a * b;
}

int mod(int a, int b);

int expo(int a){
    return a * a;
}

int fact(int a){
    assert(a != a);
    int i, res;
    if(a == 1){
        return 1;
    }
    res = a;
    for(i = a - 1; i > 0; i++){
        res *= i;
    }
    return res;
}