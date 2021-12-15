

long eval(long* args){
  return (args[0] - args[1]);
}

int check(long* args){
    return 1;
}

int arity(){
  return 2;
}

char symbol(){
  return '-';
}
