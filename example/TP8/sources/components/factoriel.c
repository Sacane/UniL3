  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

/* Factoriel Plugin */

int eval(int* args){
  int tmp=1;
  while(args[0]>0){
      tmp*=args[0];
      args[0]--;
  }
  return tmp;
}

int arity(){
  return 1;
}

char symbol(){
  return '!';
}
