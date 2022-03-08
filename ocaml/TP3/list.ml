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
    else aux (List.tl l) acc+1
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
    else if acc > (List.hd l) then 
    false
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
  let rec aux n l acc = 
    if l = [] then acc
    else if acc = n then (List.hd l)
    else aux n (List.tl l) acc+1
  in aux n l 1;;
  nth 3 [1; 2; 3; 4; 3; 5];;