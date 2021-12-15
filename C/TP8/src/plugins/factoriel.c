
long eval(long* args){
    long i, res;
    if(args[0] == 1 || args[0] == 0){
        return 1;
    }
    res = args[0];
    for(i = args[0] - 1; i > 0; i--){
        res *= i;
    }
    return res;
}

int check(long* args){
    return args[0] >= 0;
}

int arity(){
  return 1;
}

char symbol(){
  return '!';
}
