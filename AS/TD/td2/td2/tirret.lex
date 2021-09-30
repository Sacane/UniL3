%{
%}

%option nounput
%option noinput

%x TIRRET

%%

[A-Za-zé]+/"-"[\n][A-Za-zé]+                    {ECHO; BEGIN TIRRET;}
<TIRRET>"-"\n ;
<TIRRET>[A-Za-zé]+/(" "+|\n+)                   {ECHO; printf("\n");}
<TIRRET>(" "+|\n+)                              {BEGIN INITIAL;}
<TIRRET>[A-Za-zé]+" "?[:,.;!?)]+/(" "+|\n+)     {ECHO; printf("\n");}
<TIRRET>(" "+|\n+)                              {BEGIN INITIAL;}

" -"\n                                          {ECHO;}
"-"\n ;

%%

int main(){

    yylex();
    printf("\n");
    return 0;
}