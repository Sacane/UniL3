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

E: T                  {$$ = makeNode(E); addChild($$, $1); printTree($$); deleteTree($$);}
T: T DIVSTAR ID       {$$ = makeNode(T); addChild($$, $1); addChild($$, makeNode(divstar)); addChild($$, makeNode(id));}
 | ID                 {$$ = makeNode(id);}

%%

void yyerror (char *s) {
  fprintf (stderr, "%s at line %d\n", s, lineno);
}

int main(void){
  return yyparse();
}