open List;;
exception Empty_list 

(* '::' ajouter un élément en tete de liste *)
let rec integers_1 n = 
  if n < 0 then [] 
  else n :: integers_1 (n - 1);;


let integers_1_term n = 
  let rec aux acc n= 
    if n < 0 then acc
    else aux (n::acc) (n-1)
  in aux [] n;;

let rec integers_2 n = 
  if n < 0 then []
  else 
  integers_2 (n-1) @ [n];;


let integers_3 n = 
  let rec aux n = 
    if n < 0 then []
    else n :: aux (n-1) 
  in List.rev (aux n);;

  let l = integers_1 10;;
  integers_2 10;;

let three_or_more l = 
  let rec aux l acc = 
    if acc = 3 || l = [] then acc
    else aux (tl l) (acc+1)
  in aux l 0 = 3;;



let size l = 
  let rec aux l acc = 
    if l = [] then acc
    else aux (List.tl l) (acc+1)
  in aux l 0;;



let last l = 
  let rec aux l acc = 
    if l = [] then
    raise Empty_list
    else if size l = 1 then List.hd l
    else aux (List.tl l) (List.hd l)
  in aux l (List.hd l);;


let is_increasing l = 
  let rec aux l acc = 
    if l = [] then true
    else if acc > (List.hd l) then false
    else aux (List.tl l) (List.hd l)
  in aux l (List.hd l);;

(*teste si la listelest telle que ses 1er, 3e, 5e,etc. éléments sont impairs et les autres pairs*)
let even_odd l = 
  let rec aux l acc = (* acc => index de l'élément courant *)
    if l = [] then 
      true
    else if acc mod 2 <> 0 && (List.hd l) mod 2 <> 0 then false
    else if acc mod 2 = 0 && (List.hd l) mod 2 = 0 then false
    else aux (List.tl l) (acc + 1)
  in aux l 0;;

even_odd [], even_odd [1; 4; 3; 6; 9; 2], even_odd [2; 3; 3];;

let find e l = 
  let rec aux l acc = 
    if l = [] then
      false
    else if List.hd l = e then
      true
    else aux (List.tl l) (acc + 1)
  in aux l 0;;

find 3 [], find 3 [1; 2; 3], find 3 [2; 4; 6];;

let rec member e l = 
  if l = [] then []
  else if (List.hd l) = e then l
  else member e (List.tl l);;

let l = [2; 9];;
member 2 l;;
l;;
member 3 [], member 3 [1; 2; 3; 4; 3; 5], member 3 [2; 4; 6];;


let member_last e l = 
  let rec aux l acc = 
    if l = [] then acc
    else if (List.hd l) = e then aux (List.tl l) l
    else aux (List.tl l) acc
  in aux l [];; 

member_last 3 [1; 2; 3; 4; 3; 5], member_last 3 [2; 4; 6];;

let nb_occ e l = 
  let rec aux acc tmp = 
    if tmp = [] then
      acc
    else
      if (List.hd tmp) = e then
        aux (acc+1) (List.tl tmp)
      else
        aux acc (List.tl tmp)
  in aux 0 l;;

nb_occ 3 [], nb_occ 3 [1; 2; 3; 4; 3; 5], nb_occ 3 [2; 4; 6];;

let nth n l = 
  let rec aux n l i acc = 
    if l = [] then acc
    else if n = i then acc
    else aux n (List.tl l) (i+1) (List.hd l) 
  in aux n l 0 (List.hd l);;


nth 3 [1; 2; 3; 4; 3; 5], nth 3 [2; 4 ;6];;

let max_list l = 
  if l = [] then raise Empty_list
  else
    let rec aux l acc = 
      if l = [] then acc
      else if (List.hd l) > acc then aux (List.tl l) (List.hd l)
      else aux (List.tl l) acc
    in aux l 0;;


max_list [1; 2; 3; 0; 3; 0], max_list [2; 4; 6];;

(*renvoie la moyenne des nombres de la liste de flottants l.*)
let average l = 
  let rec aux l sum nb_element = 
    if l = [] then 
      if nb_element = 0. then sum /. 1.
      else sum /. nb_element
    else aux (List.tl l) (sum +. (List.hd l)) (nb_element +. 1.)
  in aux l 0. 0.;;

  average [5.; 8.5; 11.5; 15.];;


(*renvoie le nombre de maximums de la liste l. Essayer de réaliser ce
calcul en un seul parcours. renvoi une exception si la liste entré est vide. *)
let nb_max l = 
  if l = [] then raise Empty_list
  else 
    let rec aux l max nb_max = 
      if l = [] then nb_max
      else if (List.hd l) > max then aux (List.tl l) (List.hd l) 1
      else if (List.hd l) = max then aux (List.tl l) max (nb_max + 1)
      else aux (List.tl l) max (nb_max)
  in aux l 0 0;;

  nb_max [1; 2; 3; 0; 3; 0], nb_max [2; 4; 6];;

let max a b = if a >= b then a else b;;

let min a b = if a <= b then a else b;;

(*teste si la longueur de la liste l est dans l’intervalle [a; b]
(ou [b; a])*)
let size_in_range a b l = 
  let rec aux l size = 
    if l = [] then (size >= (min a b) && size <= (max a b))
    else aux (List.tl l) (size+1)
  in aux l 0;;

  let size_in_range_bis a b l = 
    let rec aux l size = 
      match l with 
      | []   -> size >= (min a b) && size <= (max a b)
      | _::l -> aux (List.tl l) (size+1)
    in aux l 0;;

  size_in_range 0 0 [], size_in_range 1 3 [0; 0], size_in_range 1 3 [0; 0; 0; 0];;

(*teste si la liste p est un motif de la liste l*)
let find_pattern p l = 
  let rec aux p_left l_left = 
    if p_left = [] then true 
    else if l_left = [] then p_left = []
    else if (List.hd p_left) = (List.hd l_left) then aux (List.tl p_left) (List.tl l_left)
    else aux p (List.tl l_left)
  in aux p l;;

find_pattern [] [1; 2], find_pattern [1; 1] [1; 2; 1], find_pattern [1; 1] [1; 2; 1; 1];;


(*let list_copy l = 
  let rec aux l copy = 
    if l = [] then copy
    else (List.hd l)::copy; aux (List.tl l) copy
  in aux (List.rev l) [];;

let l = [4; 5; 9];;
let l2 = list_copy l;;*)

let three_or_more_matched l = 
  let rec aux l acc = 
    match l, acc with 
    | [], _ -> acc 
    | _, 3 -> acc
    | _::l, _ -> aux l (acc+1)
  in aux l 0 >= 3;;

three_or_more_matched [0; 4];;