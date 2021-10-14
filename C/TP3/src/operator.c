#include "../includes/operator.h"


long sum(long a, long b){
    return a + b;
}

long sub(long a, long b){
    return b - a;
}

long divide(long a, long b){
    return b / a;
}

long mul(long a, long b){
    return a * b;
}

long mod(long a, long b){
    return b % a;
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
    long i, res;
    if(a == 1 || a == 0){
        return 1;
    }
    res = a;
    for(i = a - 1; i > 0; i--){
        res *= i;
    }
    return res;
}