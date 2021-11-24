%{

#include "exp-tpc.tab.h"

#include <string.h>

#include <stdio.h>

#include <stdlib.h>

int lineno;

int linecharno = 0;

int line_count = 1;

char* current_line = NULL;

%}

%x LONG_COMMENT SHORT_COMMENT

%option nounput

%option noinput

%option noyywrap

%%

"/*" {BEGIN LONG_COMMENT;}

"//"                {BEGIN SHORT_COMMENT;}

<LONG_COMMENT>"*/"        { BEGIN INITIAL; linecharno += yyleng; }

<LONG_COMMENT,SHORT_COMMENT>.        {linecharno += yyleng;}

<LONG_COMMENT>\n        {lineno++;linecharno=0;}

<SHORT_COMMENT>\n        {BEGIN INITIAL; lineno++;linecharno=0;}

'='|"=="|"!="	   {linecharno = linecharno + yyleng; return EQ;}

"<"|">"|"<="|">="	{linecharno = linecharno + yyleng; return ORDER;}

"+"|"-" 	        {yylval.byte = yytext[0]; linecharno = linecharno + yyleng; return ADDSUB;}

"/"|"*"|"%" 	    {yylval.byte = yytext[0]; linecharno = linecharno + yyleng; return DIVSTAR;}


[0-9]+  	{yylval.num = atoi(yytext);linecharno = linecharno + yyleng; return NUM;}

"||"        {linecharno = linecharno + yyleng; return OR;}

"&&"        {linecharno = linecharno + yyleng; return AND;}

\'.\' 	    {linecharno = linecharno + yyleng; return CHARACTER;}

" "|\t     {linecharno = linecharno + yyleng;}


[a-zA-Z_][a-zA-Z0-9_]*            {strncpy(yylval.ident, yytext, 64); linecharno = linecharno + yyleng; return IDENT;}

. 	{linecharno = linecharno + yyleng; return yytext[0];}

\n {line_count++; linecharno = 0;}

%%