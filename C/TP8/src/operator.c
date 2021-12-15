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


long expo(long x, long e)
{
    
    long y = 1;

    while (e != 0) {
        if (e % 2 == 1) {
            y = x * y;
            e = e - 1;
        } else {
            x = x * x;
            e = e / 2;
        }
    }
    return y;
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