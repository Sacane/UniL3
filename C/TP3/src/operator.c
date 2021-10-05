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

int mod(int a, int b){
    return a % b;
}

int expo(int a, int n){
    int i, res = 1;
    if(n == 0){
        return 1;
    }
    else if(n == 1){
        return a;
    }
    for(i = 2; i < n; i++){
        res *= a;
    }
    return res;
}

int fact(int a){
    assert(a != 0);
    int i, res;
    if(a == 1){
        return 1;
    }
    res = a;
    for(i = a - 1; i > 0; i--){
        res *= i;
    }
    return res;
}