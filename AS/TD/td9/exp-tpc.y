%{
/* exp-tpc.y */
/* Syntaxe des expressions en TPC */
#include <stdio.h>
int yylex();
void yyerror(char *s);
extern int lineno;
extern int line_count;
extern int linecharno;
%}
%union {
    char byte;
    int num;
    char ident[64];
    char comp[3];
}

%token <byte> CHARACTER ADDSUB DIVSTAR
%token <num> NUM
%token <ident> IDENT
%token <comp> ORDER EQ
%token OR
%token AND

%%


Exp :  Exp OR TB 
    |  TB 
    ;
TB  :  TB AND FB 
    |  FB 
    ;
FB  :  FB EQ M
    |  M
    ;
M   :  M ORDER E            {fprintf(stderr, "compar %s", $2);}
    |  E 
    ;
E   :  E ADDSUB T         {fprintf(stderr, "%c\n", $2);}             
    |  T 
    ;    
T   :  T DIVSTAR F          {fprintf(stderr, "%c\n", $2);}
    |  F 
    ;
F   :  ADDSUB F                         {fprintf(stderr, "unary %c\n", $1);}
    |  '!' F 
    |  '(' Exp ')' 
    |  NUM 
    |  CHARACTER
    |  LValue  
    |  IDENT '(' Arguments ')'      {fprintf(stderr, "fn %s\n", $1);}
    | '(' error ')'
    | IDENT '(' error ')'
    ;

LValue:
       IDENT 
    ;
Arguments:
       ListExp   
    |  
    ;
ListExp:
       ListExp ',' Exp 
    |  Exp 
    |  error ',' Exp
    ;
%%
void yyerror(char *s){

    fprintf (stderr, "%s near line %d at char : %d\n", s, line_count, linecharno);

}


int main(int argc, char **argv) {
  return yyparse();
}
