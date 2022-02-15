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
m) [1] -> list de int content 1 à la position 0 à l'initialisation
n) [1, true] -> liste de doublets int x boolean 
o) [1; true] -> erreur car les listes sont typé selon le premier élément
 

*)

(*Exercice 1.4 *)

let a = (2, 2.0);; (* int * float *)

let b = ();; (* (int, float) impossible *)

let c = ["string list"];;

let d = ([true], "bool list * string");;

let e = () (* 'a * int impossible *)

let f = [[1]];;

(* Exercice 1.5 *)

let a = 3;; (* On fait une opération sur un int -> 1 + 2 = 3 *)
let b = ();;(* Ici nous avons une erreur, car l'opérateur ne correspond pas à l'opérateur des float
Il aurait fallut écrire "+."  *)
let c = () (* Ici on utilise un opérateur entier mais la première expression est de type float, une erreur intervient donc *)

let d = 2 / 3;; (* Ici le résultat renvoi 0 car on évalue 2 entier avec un opérateur de division d'entier
Ainsi, le resultat nous retourne La valeur entière du résultat *)

let e = 7 mod 2;;  (* Pas de probleme ici, on évalue le modulo entre deux entiers, l'expression renvoi 1 *)

(* f) Modulo etant une expression d'entiers, ne peut prendre en paramètre des flottants 
let f = 7. mod 3.;; *)

(* g) L'expression renvoi la valeur entière de 8., donc 8 *)
let g = int_of_float (2. ** 3.);;

(* h) renvoi false *)
let h = 2 = 3;;

(* i) Cette expression s'évalue à "false", c'est une expression d'égalité entre deux char *)
let i = 'a' = 'b';;

(* j) Cette expression renvoi une erreur car on compare une chaine et un char *)

(* (k) Cette expression renvoi une erreur car la fonction "not" prend en argument une expr bool et non un entier *)

(* (l) not (1 = 0) Renvoi true, 1=0 est une expression boolean renvoyant false, en ajoutant le not l'expression entière devient true *)

let l = not(1 = 0);;


(* Exercice 1.6 *)

let expr1 =     
  begin 
    print_string "Debugging 1\n";
    false
  end;;

let expr2 = 
  begin 
    print_string "Debugging 2\n";
    true
  end;;

(* test opérateurs séquentiels *)



if begin
  print_string "Debugging1\n";
  false
  end
  && begin 
    print_string "Debugging2\n";
    true 
  end
  then 
    print_string "Ah\n"
  else 
    print_string "Oh\n";;


(* Exercice 2 *)

let d r = 
  let pi = acos (-1.) in 
    pi *. r ** 2.;;

let triplet_of_cylinder h r = 
  let pi = acos(-1.) in 
    let d = pi *. r ** 2. and
    p = 2. *. pi *. r in
      let a = 2. *. d +. p *. h 
      and v = d *. h 
      in (p, a, v);;

(* Exercice 3 *)

(* a) Oui on peut écrire ce morceau de code *)

(* b) Oui on peut écrire ce morceau de code, 
on change ici la définition de b *)

(* c) Oui pas de soucis ici, on peut définir c, d par c et utiliser ces deux valeurs *)

(* (d) Oui on peut écrire ce morceau de code *)

(*f ON ne peut écrire celà car on utilise pas le b dans l'expression *)

(* L'expression est correct *)

(* Exercice 3.2 *)

(* L'expression renvoi bien 3 *)

(*Exercice 4 *)

let max a b = if a >= b then a else b;;


let min a b c = 
  let tmp = if a <= b then a else b in 
  if tmp <= c then (tmp) else (c);;

(* 4.3 : Le code ne va pas, on s'attend à renvoyer un int mais le else peut renvoyer un string *)

(* 4.4 : Le problème dans le code suivant est que la syntaxe devient fausse car on utilise pas le b *)
let b = if a < 10 then "small" else "large";;

let b a = let accurate = a / 2 in 
  float_of_int accurate +. 1. ;;

let expr a b c = 
  let min a b = if a <= b then a else b in
    let tmp = min a b ** 2. in
      if c mod 3 = 0 then tmp +. 1.
      else tmp;;

(* Exercice 5 *)


let average x y z = (x + y + z) / 3;;

(* Cette fonction ne peut pas être utilisé par des flottants *)

let implies a b = 
  if (a && b) || (not a && b) || (not a && not b) then true
  else false;;

let inv (a, b) = (b, a);;

let inv' couple = 
  (snd couple, fst couple);;

let f_one () = 1;;

(* Exo 5.6 *)
let m = 3;; (* affiche val m : int = 3 *)

let f x = x;; (* affiche 'a -> 'a = <fun> *)

let g x = x + m;; (*affiche int -> int = <fun> *)

f 4;; (*affiche int = 4 *)

g 4;; (*affiche - : int = 7*)

let m = 5;; (*affiche val m : int = 5*)

g 4;; (* affiche - : int = 9 *)



