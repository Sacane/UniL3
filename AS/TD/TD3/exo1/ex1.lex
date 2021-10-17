%{

%}

%option noyywrap
%option nounput
%option noinput

%%

\n {return 0;}
. {return yytext[0];}

%%