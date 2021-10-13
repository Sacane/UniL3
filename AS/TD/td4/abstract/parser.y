%{

#include <stdio.h>
void yyerror(char *s);
int yylex(void);
extern int lineno;

%}
%code requires {
#include "tree.h"
struct Node* root;
}

%union{
  Node *node;
}

%type <node> E T DIVSTAR ID
%token DIVSTAR 
%token ID

%%

E: T                  {printTree($$); deleteTree($$);}
T: T DIVSTAR ID       {$$ = makeNode(divstar); addChild($$, $1); addChild($$, makeNode(id));}
 | ID                 {$$ = makeNode(id);}

%%

void yyerror (char *s) {
  fprintf (stderr, "%s at line %d\n", s, lineno);
}

int main(void){
  return yyparse();
}