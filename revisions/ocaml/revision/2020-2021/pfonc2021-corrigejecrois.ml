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

(* ecriture d'un List.init *)
let init len f = 
    let rec aux i acc =
        if i < 0 then
            acc
        else
            aux (i - 1) ((f i)::acc)
    in aux (len - 1) []

(* Question 1. *)
let decomposer_entier n = init (n + 1) (fun it -> (n - it, n - (n - it)))

(* Question 2. *)
let ajouter_noeud_unaire arbres = List.fold_right (fun next acc -> Unaire(next)::acc) arbres []

(* Question 3. *)
let ajouter_noeud_binaire arbres1 arbres2 =
    let aux e =
        List.fold_right (fun next acc -> Binaire(e, next)::acc) arbres2 []
    in List.fold_left (fun acc next -> acc @ (aux next) ) [] arbres1


(* Question 4. *)
let taille arb =
    let rec aux a acc =
        match a with
        | Feuille(_) -> acc
        | Unaire(f) -> aux f (acc + 1)
        | Binaire(fg, fd) -> let tmp = aux fg (acc + 1) in aux fd tmp
    in aux arb 0

(* Question 5. *)
let rec generer_arbres v n =
    if n = 0 then
        [Feuille(v)]
    else
        let lst1 = ajouter_noeud_unaire (generer_arbres v (n - 1))
        and decomp = decomposer_entier (n - 1) in
        let lst2 = List.fold_left (fun acc (a, b) -> acc @ (ajouter_noeud_binaire (generer_arbres v a) (generer_arbres v b))) [] decomp
        in lst1 @ lst2

(* Question 6. *)
let rec developper arb =
    match arb with
        | Unaire(f) -> Binaire(developper f, developper f)
        | Binaire(fg, fd) -> Binaire(developper fg, developper fd)
        | _ -> arb

(* Question 7. *)
let rec factoriser arb =
    match arb with
        | Binaire(fg, fd) when fg <> fd -> Binaire(factoriser fg, factoriser fd)
        | Binaire(fg, fd) -> Unaire(factoriser fg)
        | Unaire(f) -> Unaire(factoriser f)
        | _ -> arb


(* EXERCICE 2 *)

(* Les types necessaires a la representation des expressions. *)
type chiffre = int
type ecriture = chiffre list
type terme = ecriture list
type expression = terme list

(* Une exception pour gerer les cas ou une expression vide est fournie. *)
exception ExpressionVide

(* Question 1. *)
let s1 = [[[1]; [2]; [3]; [4]]; [[5]]; [[6]]; [[7]; [8]]; [[9]]]

let s2 = [[[1]]; [[2]; [3]]; [[4]]; [[5]]; [[6; 7]]; [[8]]; [[9]]]


(* Question 2. *)
let somme lst = List.fold_left (fun acc next -> acc + next) 0 lst

let produit lst = List.fold_left (fun acc next -> acc * next) 1 lst

(* Question 3. *)
let valeur_ecriture ecr =
    let (res, _) = List.fold_right (fun next (res, pow) -> (res + next * pow, pow * 10)) ecr (0, 1)
    in res

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
let concatener_images f lst = List.fold_left (fun acc next -> acc @ (f next)) [] lst

(* Question 7. *)
let incorporer_chiffre ch exp =
    if exp = [] then
        raise ExpressionVide
    else
        let l1 = [[ch]]::exp
        and l2 = ([ch]::(List.hd exp))::(List.tl exp)
        and l3 = ((ch::(List.hd (List.hd exp)))::(List.tl (List.hd exp)))::(List.tl exp)
        in [l1; l2; l3]

(* Question 8. *)
let etendre_expressions ch exp_lst = concatener_images (fun it -> incorporer_chiffre ch it) exp_lst

(* Question 9. *)
let generer_expressions ch_lst =
    if ch_lst = [] then
        []
    else
        let rev = List.rev ch_lst in
            List.fold_left (fun acc next -> etendre_expressions next acc) [[[[List.hd rev]]]] (List.tl rev)

(* Question 10. *)
let siecles ch_lst k =
    generer_expressions ch_lst
    |> List.filter (fun it -> (valeur_expression it) = k)
    

(* FIN *)

