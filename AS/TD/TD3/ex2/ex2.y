%{

#include <stdio.h>

void yyerror(char *s);
int yylex(void);
extern int lineno;
%}

%token OR
%token AND
%token NO
%token TRUE
%token FALSE
%token OPEN
%token CLOSE
%%

E: E OR T 
 | 
 T
 ;

T: T AND F 
 |
 F
 ;
 
F: NO F
 | OPEN E CLOSE 
 | TRUE
 | FALSE
 ;

%%

void yyerror (char *s) {
  fprintf (stderr, "%s at line %d\n", s, lineno);
}

int main(void){
  return yyparse();
}