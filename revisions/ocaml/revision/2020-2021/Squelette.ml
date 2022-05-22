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
    let rec aux n n2 acc = 
        match n, n2 with
        |   l, l2 when l2 = 0 -> acc @ [(l, l2)] 
        |   l, l2 -> acc @ [(l, l2)] @ aux (l+1) (l2-1) acc
        in aux 0 n [];;

decomposer_entier 0;;
decomposer_entier 1;;
decomposer_entier 4;;

(* Question 2. *)
let ajouter_noeud_unaire arbres =
    List.map (fun id -> Unaire(id)) arbres;;

ajouter_noeud_unaire [Feuille 1; Unaire (Feuille 2); Binaire (Feuille 1, Unaire (Feuille 4))];;

(* Question 3. *)
let ajouter_noeud_binaire arbres1 arbres2 =
    let rec aux a a2 acc = 
        match a, a2 with
        |   [], _ -> acc
        |   h::t, [] -> acc @ aux t arbres2 acc
        |   h::t, h'::t' -> acc @ [Binaire (h, h')] @ aux a (t') acc
    in aux arbres1 arbres2 []

;;
ajouter_noeud_binaire
[Feuille 1; Feuille 2]
[Unaire (Feuille 2); Binaire (Feuille 0, Feuille 1)];;

(* Question 4. *)
let taille arb =
    let rec aux arb count = 
        match arb with 
        |   Binaire(a, b) -> count + aux a 1 + aux b 1
        |   Unaire(a) -> count + aux a 1
        |   Feuille(v) -> 0
    in aux arb 1;;
;;

taille arb1;;
taille arb2;;
taille (Feuille 512)
;;

(* Question 5. *)
let rec generer_arbres v n =
    if n = 0 then [Feuille v]
    else 
        let lst1 = ajouter_noeud_unaire (generer_arbres v (n - 1))
        and decomp = decomposer_entier (n-1) in 
        let lst2 = List.fold_left (fun acc (a, b) -> acc @ (ajouter_noeud_binaire (generer_arbres v a) (generer_arbres v b))) [] decomp
    in lst1 @ lst2;;


generer_arbres 0 2;;

(* Question 6. *)
let rec developper arb =
    match arb with
    |   Feuille a -> Feuille a
    |   Unaire t -> Binaire (developper t, developper t)
    |   Binaire(a, b) -> Binaire(developper a, developper b);;

developper (arb1);;
developper arb2;;

(* Question 7. *)
let rec factoriser arb =
    match arb with 
    |   Binaire (a, b) when a <> b -> Binaire (factoriser a, factoriser b)
    |   Binaire (a, b) -> Unaire (factoriser a)
    |   Unaire(a) -> Unaire(factoriser a)
    |   Feuille(_) -> arb
    ;;
factoriser (factoriser arb1);;
factoriser arb2;;

(* EXERCICE 2 *)

(* Les types necessaires a la representation des expressions. *)
type chiffre = int
type ecriture = chiffre list
type terme = ecriture list
type expression = terme list

(* Une exception pour gerer les cas ou une expression vide est fournie. *)
exception ExpressionVide

(* Question 1. *)
let s1  =
    [[[1]; [2]; [3]; [4]]; [[5]; [6]]; [[7]; [8]]; [[9]]]

let s2 =
    [[[1]]; [[2]; [3]]; [[4]]; [[5]]; [[6; 7]]; [[8]]; [[9]]]

(* Question 2. *)
let somme lst =
    List.fold_left (+) 0 lst;;
somme [1; 2; 3; 1];;

let produit lst =
    List.fold_left (fun acc el -> el * acc) 1 lst;;
produit [1; 2; 3; 1];;

(* Question 3. *)
let valeur_ecriture ecr =
    let rep = List.fold_left (fun acc x -> String.concat acc [""; (string_of_int x)]) "" ecr
    in int_of_string rep;;


valeur_ecriture [1; 5; 3];;

(* Question 4. *)
let valeur_terme ter =
    ter |> List.map valeur_ecriture |> produit;;

valeur_terme [];;
valeur_terme [[1; 5; 3]];;
valeur_terme [[1; 3; 5]; [2; 8; 1; 1]];;

(* Question 5. *)
let valeur_expression exp =
    exp |> List.map valeur_terme |> somme;;

valeur_expression [[[1; 3; 5]; [2; 8; 1; 1]]; [[2; 2]; [1]; [1; 4; 4]]];;

valeur_expression [[[1]]; [[2]; [3]]; [[4]]; [[5]]; [[6; 7]]; [[8]]; [[9]]];;

(* Question 6. *)
let concatener_images f lst =
    lst |> List.map f |> List.concat;;
    concatener_images (fun x -> [x; 2 * x; 4 * x]) [0; 1; 2; 3];;

(* Question 7. *)
let incorporer_chiffre ch exp =
    if exp = [] then raise ExpressionVide
    else
        [
            [[ch]] :: exp;
            ([ch]::List.hd exp)::List.tl exp;
            ((ch::(List.hd (List.hd exp)))::(List.tl (List.hd exp)))::(List.tl exp)
        ];;
incorporer_chiffre 1 [[[2; 3]; [4]]; [[5]; [6]]];;

(* Question 8. *)
let etendre_expressions ch exp_lst =
    concatener_images (incorporer_chiffre ch) exp_lst;;

let exp1 = [[[2; 3]; [4]]; [[5]; [6]]] in 
let exp2 = [[[2]]] in 
etendre_expressions 1 [exp1; exp2];;

(* Question 9. *)
let generer_expressions ch_lst =
    ()

(* Question 10. *)
let siecles ch_lst k =
    ()

(* FIN *)

