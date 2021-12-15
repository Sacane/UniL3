long eval(long* args){
  return (args[1] * args[0]);
}

int check(long* args){
    return 1;
}

int arity(){
  return 2;
}

char symbol(){
  return '*';
}
