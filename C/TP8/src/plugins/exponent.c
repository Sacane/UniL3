
long eval(long* args){
    long y = 1;
    long x = args[0];
    long e = args[1];
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

int check(long* args){
    return 1;
}

int arity(){
  return 2;
}

char symbol(){
  return '^';
}
