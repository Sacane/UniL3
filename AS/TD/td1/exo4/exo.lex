%{
/*Declarations*/
int count = 0;
%}

%option noyywrap
%option nounput
%option noinput
/* Regles */

%%
[a-zA-Z]{5,} {ECHO;}
[' '] {printf(" \n");}
[a-zA-Z]* ;
.|\n ;
<<EOF>> {printf("\n"); return 0;}
%%

int main(){
    yylex();
    return 0;
}

