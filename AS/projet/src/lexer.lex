%{

/*ProjetAS-Lexer_v1*/

%}

%option nounput
%option noinput
%option noyywrap

%x COMETOILE COMBARRE   /*  1) Essaye d'utiliser des noms plus pertinent et surtout en anglais si possible
                            (toutes nos variables dans ce projets seront en anglais) */
                        

%%

"/*" {BEGIN COMETOILE;}

<COMETOILE>. {;} /* 2) Pas forcément utile ici, la règle à la ligne 21 s'en occupe déjà  */

<COMETOILE>"*/" {BEGIN INITIAL;}

"//" {BEGIN COMBARRE;}

<COMBARRE>.   {;}
<COMBARRE>[\n]$ {BEGIN INITIAL;} /* 3) Tu n'es pas obligé d'utiliser les crochets d'ailleurs y'a moyen que 
                                    ça fasse une erreur et qu'il comprenne le caractère '\' ou 'n'.
                                    (Je sais pas par contre à quoi sert le dolar ?) */


[*%/] {return DIVSTAR;}
[+-] {return ADDSUB;}
[a-zA-Z_][0-9a-zA-Z_]* {return IDENT;}
"=>"| ">"| "<" || " <=" {return ORDER;}
"int" | "char" {return TYPE;}
"==" | "!=" {return EQ;}
"||" {return OR;}
"&&" {return AND;}
[0-9][0-9]* {return NUM;}
[a-zA-Z] {return CHARACTER;}


(while|for|if|else|return)/\( {;} /* 4) Subdivise chaque lexème pour qu'elles retournent les tokens correspondant,
                                     regarde les tokens dans la grammaire du parser.y */

. {;}


%%