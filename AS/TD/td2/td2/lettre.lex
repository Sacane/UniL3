%{
    #include <stdio.h>
    int counter = 0;
%}

%option nounput
%option noinput

%%

[A-Za-z]    {ECHO; counter++; if(counter % 5 == 0){ printf("\n");}}
[^A-Za-z] ;

%%

int main(){

    yylex();
    printf("\n");
    return 0;
}


