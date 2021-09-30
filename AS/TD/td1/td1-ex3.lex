%{
/* td1-ex3.lex */
/* Chiffrement par substitution */
%}
%option noyywrap
%option nounput
%option noinput
%%
a return 'e';
c return 'd';
d return 'c';
e return 'a';
é return 'g';
g return 'e';
i return 's';
l return 'u';
m return 'p';
n return 'r';
o return 't';
p return 'm';
r return 'n';
s return 'i';
t return 'o';
u return 'l';
A return 'E';
C return 'D';
D return 'C';
E return 'A';
É return 'G';
G return 'E';
I return 'S';
L return 'U';
M return 'P';
N return 'R';
O return 'T';
P return 'M';
R return 'N';
S return 'I';
T return 'O';
U return 'L';
<<EOF>> return 0;
.|\n return yytext[0];
%%
int main() {
    char c = yylex();
    while(c != 0){
        c = yylex();
        printf("%c", c);
    }
    return 0;
}