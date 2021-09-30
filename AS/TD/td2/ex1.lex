%{
    /*Declarations*/
%}

%x COMM 
%option nounput
%option noinput


%%

"/*" {BEGIN COMM;}
<COMM>"*/" {BEGIN INITIAL;}
<COMM>.|\n ;


[a-zA-Z_][a-zA-Z_0-9]*/[ \t\n]*"(" {ECHO; printf(" ");}
.|\n ;
"//".*\n ;

%%
int main(){
    yylex();
    printf("\n");
    return 0;
}