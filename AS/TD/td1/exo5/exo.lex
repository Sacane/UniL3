%{
/*Declarations*/
int count = 0;
%}

%option noyywrap
%option nounput
%option noinput
/* Regles */

%%
[a-zA-Z] {return yytext[0];}
<<EOF>> {return 0;}
.|\n return yytext[0];

%%

int main(){
    int c = yylex();
    while(c != 0){
        c = yytext[0];
        c = (c+1) % 26;
        printf("%c", c);
    }
    return 0;
}