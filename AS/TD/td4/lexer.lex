%{
/* Declaration */
#include "parser.tab.h"
#include <stdlib.h>
int lineno = 0; 
#include "tree.h"
%}


%option noyywrap
%option nounput
%option noinput

%%

\n lineno++;
"*"|"/"|"%" {return DIVSTAR;}
[0-9]+ {return ID;}
[ \t]* ;


%%