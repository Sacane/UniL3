  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

/* Division Plugin */

int eval(int* args){
  if(args[1] == 0)
    return 0;
  return (args[0] / args[1]);
}

int arity(){
  return 2;
}

char symbol(){
  return '/';
}
