open List;;
open String;;
exception Empty_list 

let sqr x = x * x;;

let f_sum (f : int -> int) a b = f a + f b;;

let my_list = [3; 12; 3; 40; 6; 4; 6; 0];;


f_sum sqr 2 3;;

f_sum (fun x -> x + 1) 2 3;;

let new_f_sum (f : int -> int) a = fun b -> f a + f b;;

new_f_sum sqr 2;;

(new_f_sum sqr 2) 3;;


List.map (fun x -> sqr x) my_list;;


let mul2 : 'a -> int = fun x -> x*2;;

List.map mul2 my_list;;

let f () = 0;;

let make_list (make : unit -> 'a) num = 
  let rec aux l counter = match counter with
  | n when n = num -> l
  | n -> l @ [make ()] @ aux l (counter+1)
  in aux [] 0;;

make_list f 8;;

make_list (Random.bool) 64;;

let l_16 = make_list (fun x -> Random.int 100) 16;;

(* Exercice 2 *)

let entiers = [2; 5; 7; 3; 12; 4; 9; 2; 11];;
let animaux = ["Wombat"; "aXolotl"; "pangolin"; "suricate"; "paresseuX"; "quoKKa"; "lemurien"];;

(* 1. calculer la liste des longueurs des chaînes de caractères de la liste animaux ; *)
List.map (fun x -> String.length x) animaux;;

(* 2. calculer la liste de tous les animaux de la liste animaux écrits en majuscules ; *)

List.map (fun s -> String.uppercase_ascii s) animaux;;

(* 3. calculer la liste des chaînes de la 
liste animaux qui sont écrites en minuscules *)

List.filter (
  fun s -> let as_lower = String.lowercase_ascii s in
  if String.equal s as_lower then true else false
) animaux;;

(* 4. calculer la liste des noms des animaux de longueurs paires *)

List.filter (
  fun s -> String.length s mod 2 = 0 
) animaux;;

List.map (fun x -> if x mod 2 = 0 then (x, "pair") else (x, "impair")) entiers;;


(* 6. calculer une liste de listes composées de 
n fois la valeur de n, pour chaque entier n dans
la liste entiers ; *)



List.map (
  fun e -> let rec aux l i = match i with
  | n when n = e -> l
  | _ -> aux (l @ [e]) (i+1)
  in aux [] 0
) entiers;;


(* 7. tester s’il existe une élément de la liste
 animaux qui commence par le caractère ’s’  *)

List.exists (fun e -> e.[0] = 's') animaux;;

(* 8. tester si tous les éléments de la liste animaux
 sont de longueur congrue à 2 modulo 5*)

List.for_all (fun e -> (String.length e) mod 5 = 2) animaux;;

(* Exercice 3 *)

let sum l = List.fold_left (+) 0 l;;

sum entiers;;

(+);;
let f = fun e -> e + 1;;


let size l = List.fold_left (fun acc x -> 1 + acc) 0 l;;

size entiers;;

let last l = List.find (fun e -> true) (List.rev l);;

let nb_occ e l = List.fold_left (fun acc x -> if x = e then 1 + acc else acc) 0 l;;

nb_occ 2 entiers;;
(* expect 2 *)

nb_occ 11 entiers;;
(*expect 1*)

nb_occ 99 entiers;;
(*expect 0*)

let max_list l = List.fold_left (fun acc x -> if x <= acc then acc else x) (List.hd l) l;;

max_list entiers;;


let average l = 
  let (acc, n) = List.fold_left (fun (acc, n) x -> (acc + x, n + 1)) (0, 0) l 
  in (float_of_int acc) /. (float_of_int n);;


average entiers;;
(* expect 6.11111111111111072 *)

(*Exercice 4 *)

let greater_0 x = x >= 0;;

let rec my_for_all (p : int -> bool) l = match l with 
  | [] -> true
  | h::t when (p h) = false -> false
  | _::t -> my_for_all p t
  ;;

let numbers = [10; -5; 2; 4];;
let l_greater0 = [9; 2; 4; 102];;

my_for_all greater_0 numbers;;
my_for_all greater_0 l_greater0;;


let my_for_all2 (p : int -> bool) l = List.fold_left (fun acc x -> if (p x) = false then false else acc) true l;;

my_for_all2 greater_0 numbers;;
my_for_all2 greater_0 l_greater0;;

let my_for_all3 (p: int -> bool) l = List.fold_right (fun x acc -> if (p x) = false then false else acc) l true;;

my_for_all3 greater_0 numbers;;
my_for_all3 greater_0 l_greater0;;

let my_exists (p: int -> bool) l = List.fold_left (fun acc x -> if (p x) then true else acc) false l;;

my_exists (fun x -> x <= 0) l_greater0;; (* expect false *)
my_exists (fun x -> x <= 0) numbers;; (* expect true *)

let none (p: int -> bool) l = List.fold_left (fun acc x -> if (p x) then false else acc) true l;;

let not_all (p: int -> bool) l = List.fold_left (fun acc x -> if (p x) = false then true else acc) false l;;

let rec ordered (p: int -> int -> bool) l = match l with 
| [] -> true
| [e] -> true
| e1::e2::lst -> if p e1 e2 then ordered p (e2::lst) else false;;

(<);;

ordered (<) [1; 2; 3];;

ordered (<) [1; 4; 2];;

let filter2 (p: int -> int -> bool) l l2 = 
  let rec aux l1 l2 res = match l1, l2 with
| [], [] -> res
| h::t, h'::t' when p h h' = true -> res @ aux t t' ((h, h') :: [])
| _::t, _::t' -> res @ aux t t' []
| _, _ -> raise Empty_list
in aux l l2 [];;

filter2 (<) [2; 2; 3] [1; 4; 5];;


(* Exercice 5 *)


let rec perm l =
  let rec insert e lst =
    match lst with
    | [] -> [[e]]
    | h::t -> (e::lst) :: (List.map (fun l -> h::l) (insert e t)) in
  match l with
  | [] -> [l]
  | h::t -> (perm t) |> List.map (insert h) |> List.flatten;;


perm [1; 2];;

perm [1; 2; 3; 4];;




