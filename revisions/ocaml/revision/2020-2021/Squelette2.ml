(* Examen de programmation fonctionnelle - L3 Informatique 2020--2021. *)

(* Prenom : REMPLIR
 * Nom : REMPLIR
 * Groupe : REMPLIR
*)

(* - Ce fichier doit pouvoir etre interprete sans erreur par la commande
 *       ocaml Squelette.ml
 *   quitte a ce que les types ne soient pas respectes.
 *
 * - Les en-tetes des fonctions sont donnes ici. Il est possible de les changer pour ajouter
 *   "rec" par exemple.
 *
 * - Toutes les fonctions du squelette renvoient pour le moment la valeur () du type unit
 *   simplement afin de rendre le fichier interpretable.
*)

(* DEBUT *)

(* EXERCICE 1 *)

(* Le type des arbres unaires binaires. *)
type 'v arbre =
  |Feuille of 'v
  |Unaire of 'v arbre
  |Binaire of 'v arbre * 'v arbre

(* Les deux arbres exemple. *)
let arb1 =
  Binaire (
    Binaire (
      Binaire (
        Unaire (Feuille 1),
        Unaire (Feuille 1)),
      Unaire (
        Unaire (Feuille 1))),
    Binaire (
      Unaire (
        Unaire (Feuille 1)),
      Unaire (
        Unaire (Feuille 2))))

let arb2 =
  Unaire (
    Binaire (
      Binaire (
        Binaire (
          Binaire (
            Unaire (Feuille 2),
            Feuille 0),
          Feuille 1),
        Unaire (Feuille 0)),
      Unaire (Unaire (Feuille 2))))

(* Question 1. *)
let decomposer_entier n =
  List.init (n+1) (fun i -> (i, n-i))

(* Question 2. *)
let ajouter_noeud_unaire arbres =
  List.map (fun it -> Unaire(it)) arbres

(* Question 3. *)
let ajouter_noeud_binaire arbres1 arbres2 =
  List.map (fun a ->
      List.map (fun b -> Binaire(a, b)) arbres2
    ) arbres1
  |> List.concat

(* Question 4. *)
let rec taille arb =
  match arb with
  | Unaire(t) -> (taille t) + 1
  | Binaire(a, b) -> (taille a) + (taille b) + 1
  | Feuille(_) -> 0

(* Question 5. *)
let rec generer_arbres v n =
  if n = 0 then
    [Feuille(v)]
  else
    let lst1 = ajouter_noeud_unaire (generer_arbres v (n-1))
    and lst2 = 
      decomposer_entier (n-1)
      |> List.map (fun (i, j) -> ajouter_noeud_binaire (generer_arbres v i) (generer_arbres v j))
      |> List.flatten
    in lst1 @ lst2

(* Question 6. *)
let rec developper arb =
  match arb with
  | Unaire(t) -> Binaire(developper t, developper t)
  | Binaire(a, b) -> Binaire(developper a, developper b)
  | Feuille(_) -> arb

(* Question 7. *)
let rec factoriser arb =
  match arb with
  | Binaire(a, b) when a <> b -> Binaire(factoriser a, factoriser b)
  | Binaire(a, b) -> Unaire(factoriser a)
  | Unaire(t) -> Unaire(factoriser t)
  | Feuille(_) -> arb


(* EXERCICE 2 *)

(* Les types necessaires a la representation des expressions. *)
type chiffre = int
type ecriture = chiffre list
type terme = ecriture list
type expression = terme list

(* Une exception pour gerer les cas ou une expression vide est fournie. *)
exception ExpressionVide

(* Question 1. *)
let s1 =
  [[[1];[2];[3];[4]];[[5]];[[6]];[[7];[8]];[[9]]]

let s2 =
  [[[1]];[[2];[3]];[[4]];[[5]];[[6;7]];[[8]];[[9]]]

(* Question 2. *)
let somme lst =
  List.fold_left (fun acc next -> acc + next) 0 lst

let produit lst =
  List.fold_left (fun acc next -> acc * next) 1 lst

(* Question 3. *)
let valeur_ecriture ecr =
  List.fold_left (fun acc next -> acc*10 + next) 0 ecr

(* Question 4. *)
let valeur_terme ter =
  ter
  |> List.map valeur_ecriture
  |> produit


(* Question 5. *)
let valeur_expression exp =
  exp
  |> List.map valeur_terme
  |> somme

(* Question 6. *)
let concatener_images f lst =
  List.map f lst |> List.concat

(* Question 7. *)
let incorporer_chiffre ch exp =
  if exp = [] then
    raise ExpressionVide
  else [
    [[ch]]::exp;
    ([ch]::(List.hd exp))::(List.tl exp);
    ((ch::(List.hd (List.hd exp)))::(List.tl (List.hd exp)))::(List.tl exp)
  ]

(* Question 8. *)
let etendre_expressions ch exp_lst =
  concatener_images (incorporer_chiffre ch) exp_lst

(* Question 9. *)
let generer_expressions ch_lst =
  let it = List.rev ch_lst in
  List.fold_left (fun acc next -> etendre_expressions next acc) [[[[List.hd it]]]] (List.tl it)

(* Question 10. *)
let siecles ch_lst k =
  generer_expressions ch_lst
  |> List.filter (fun it -> valeur_expression it = k)

(* FIN *)

