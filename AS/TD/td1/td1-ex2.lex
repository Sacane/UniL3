%{
/*Declarations*/

int engWd = 0;
int frWd = 0;
%}

%option noyywrap
%option nounput
%option noinput
/* Regles */

%%

the   {printf("English "); engWd++;}
of    {printf("English "); engWd++;}
and   {printf("English "); engWd++;}
to    {printf("English "); engWd++;}
a     {printf("English "); engWd++;}
his   {printf("English "); engWd++;}
in    {printf("English "); engWd++;}
with  {printf("English "); engWd++;}
I     {printf("English "); engWd++;}
which {printf("English "); engWd++;}
de  {printf("français "); frWd++;;}
à   {printf("français "); frWd++;}
le  {printf("français "); frWd++;}
la  {printf("français "); frWd++;}
et  {printf("français "); frWd++;}
il  {printf("français "); frWd++;}
les {printf("français "); frWd++;}
un  {printf("français "); frWd++;}
en  {printf("français "); frWd++;}
du  {printf("français "); frWd++;}
[a-zA-ZâàçêéèëîïôûùüœÂÀÇÊÉÈËÎÏÔÛÙÜŒ]+ ;
.|\n ;
<<EOF>> {if(frWd > engWd) printf("Plutot français\n"); else printf("Plutot anglais"); return 0;}
%%

