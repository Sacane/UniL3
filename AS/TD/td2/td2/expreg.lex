%{

%}

%x DQUOTES

%option nounput
%option noinput


%%


\"                                      {BEGIN DQUOTES;}
<DQUOTES>\"                             {BEGIN INITIAL;}
<DQUOTES>.|\n ;

[A-Za-z_][A-Za-z_0-9]*/[ \t\n]*"("      {printf("%s\n", yytext);}
.|\n ;
"//".*\n ;
"/*"(.|\n)*"*/" ;

%%

int main(){

    yylex();
    printf("\n");
    return 0;
}