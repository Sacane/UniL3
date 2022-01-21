  /*____________°\
 /.,------------,.\     EDITOR = ORHAN UYAR
///  .=^^^^^^^\__|\\    UNIVESITY = Gustave Eiffel
\\\   `------.   .//    LINK = www.brotherkey.fr
 `\\`--...._  `;//'     PS = HAVE FUN
   `\\.-,___;.//'
     `\\-..-//'
        \*/

/* Exponentiel Plugin */
#include <math.h>

int eval(int* args){
  return (pow(args[0],args[1]));
}

int arity(){
  return 2;
}

char symbol(){
  return '^';
}
