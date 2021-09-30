%{

%}

%x DOCSTRING 
%x DQUOTES

%option nounput
%option noinput


%%

"/*"                                    {BEGIN DOCSTRING;}
<DOCSTRING>"*/"                         {BEGIN INITIAL;}
<DOCSTRING>.|\n ;

\"                                      {BEGIN DQUOTES;}
<DQUOTES>\"                             {BEGIN INITIAL;}
<DQUOTES>.|\n ;

[A-Za-z_][A-Za-z_0-9]*/[ \t\n]*"("      {ECHO;}
.|\n ;
"//".*\n ;

%%

int main(){

    yylex();
    printf("\n");
    return 0;
}