%{
    
#include "ex2.tab.h"
#include <string.h>
#include <stdlib.h>

int lineno = 0;
%}

%option noyywrap
%option nounput
%option noinput


%%

\n {lineno++;}
"ou" return OR;
"et" return AND;
"non" return NO;
"vrai" return TRUE;
"faux" return FALSE;
"(" return OPEN;
")" return CLOSE;
. ;



%%



