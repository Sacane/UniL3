(* 1) Si l'on évalue 33 dans le toplevel, nous ne pouvons pas utiliser les flèches directionnelles *)

(* 2) En lançant rlwrap, nous pouvons refaire la manipulation de la question 1 mais en utilisant la flèche du haut nous pouvons 

accéder à l'historique des entrées du toplevel.

*)

(* 
a) 2 -> int 
b) 2.0 -> float
c) 2,0 -> int * int (2, 0)
d) 2;0 -> warning car ';' est un opérateur de fin d'utilisation
e) (2, 0) -> même que c)

f) (2; 0) -> Même que d)
g) a n'est pas une expression caml
h) 'a' -> char
i) "a" -> string
j) true -> bool

k) () -> unit
l) [] -> list
m) [1] -> list de int avec 1 dedans à l'initialisation
n) [1, true] -> liste de multiplets int x boolean 
o) [1; true] -> erreur car les listes sont typé selon le premier élément
 

*)