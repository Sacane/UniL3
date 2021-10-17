%{

#include <stdio.h>
void yyerror(char *s);
int yylex(void);

%}



%%

S: 'a'S
     | 'b'
     ;

%%

void yyerror (char *s) {
  fprintf (stderr, "%s\n", s);
}

int main(int argc, char *argv[])
{
    return yyparse();
}
