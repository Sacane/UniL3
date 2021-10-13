#include "../includes/operator.h"

long is_binary_op(char operator){
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


long sum(long a, long b){
    return a + b;
}

long sub(long a, long b){
    return a - b;
}

long divide(long a, long b){
    return a / b;
}

long mul(long a, long b){
    return a * b;
}

long mod(long a, long b){
    return a % b;
}

long expo(long a, long n){
    long i, res = 1;
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

long fact(long a){
    assert(a != 0);
    long i, res;
    if(a == 1){
        return 1;
    }
    res = a;
    for(i = a - 1; i > 0; i--){
        res *= i;
    }
    return res;
}