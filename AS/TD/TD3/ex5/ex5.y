%{

#include <stdio.h>
void yyerror(char *s);
int yylex(void);

%}



%%

S: 'a'S
     | S'a'
     | 'a''a'S
     | 'a'S'a'
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
