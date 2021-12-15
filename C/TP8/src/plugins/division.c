#include <stdio.h>



long eval(long* args){
  return (args[0] / args[1]);
}

int check(long* args){
  if(args[1] == 0){
    fprintf(stderr, "W:divide by zero\n");
    return 0;
  }
    return 1;   
}

int arity(){
  return 2;
}

char symbol(){
  return '/';
}
