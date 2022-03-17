open List;;
exception Empty_list 



let rec integers_1 n = 
  match n with 
  | p when p < 0 -> []
  | _ -> n :: integers_1 (n-1);;




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
  let rec aux l res = match l with 
  | [] -> res
  | head::tail -> aux tail (res+1)
  in aux l 0;;
  size [], size [3; 1; 4; 5; 2];;


let last l = 
  let rec aux l acc = match l with
  | [] -> raise Empty_list
  | h::t when t = [] -> h
  | h::t -> aux t h
  in aux l (List.hd l);;

last [1], last [3; 1; 4; 5; 2];;


let is_increasing l = 
  let rec aux l acc = match l, acc with 
  | [], _ -> true
  | h::t, a when a > h -> false
  | h::t, _ -> aux t h
  in aux l 0;;



  is_increasing [], is_increasing [3; 1; 4; 5; 2], is_increasing [1; 3; 5; 5; 7];;

(*teste si la listelest telle que ses 1er, 3e, 5e,etc. éléments sont impairs et les autres pairs*)


let even_odd l = 
  let rec aux l index = match l, index with
  | [], _ -> true
  | h::t, i when i mod 2 <> 0 && h mod 2 <> 0 -> false
  | h::t, i when i mod 2 = 0 && h mod 2 = 0   -> false
  | h::t, i -> aux t (i+1)
  in aux l 0;;

even_odd [], even_odd [1; 4; 3; 6; 9; 2], even_odd [2; 3; 3];;


let find e l = 
  let rec aux l i = match l with
  | [] -> false
  | h::t when h = e -> true
  | h::t -> aux t (i+1)
  in aux l 0;;

find 3 [], find 3 [1; 2; 3], find 3 [2; 4; 6];;



let rec member e l = match l with
  | [] -> []
  | h::t when h = e -> h::t
  | h::t -> member e t;;

  member 3 [], member 3 [1; 2; 3; 4; 3; 5], member 3 [2; 4; 6];;



let member_last e l = 
  let rec aux l res = match l with
  | [] -> res
  | h::t when h = e -> aux t l
  | h::t -> aux t res
  in aux l [];;
    
member_last 3 [1; 2; 3; 4; 3; 5], member_last 3 [2; 4; 6];;


let nb_occ e l = 
  let rec aux res i = match res with
  | [] -> i
  | h::t when h = e -> aux t (i+1)
  | h::t -> aux t i
  in aux l 0;;

nb_occ 3 [], nb_occ 3 [1; 2; 3; 4; 3; 5], nb_occ 3 [2; 4; 6];;



let nth n l = 
  let rec aux n l i res = match l, n with 
  | li, value when value = i || li = [] -> res
  | h::t, value -> aux n t (i+1) h
  | [], _ -> raise Empty_list
  in aux n l 0 (List.hd l);;


nth 3 [1; 2; 3; 4; 3; 5], nth 3 [2; 4 ;6];;



let max_list l = 
  if l = [] then raise Empty_list
  else let rec aux l i = match l with 
  | [] -> i
  | h::t when h > i -> aux t h
  | h::t -> aux t i
  in aux l 0;;


max_list [1; 2; 3; 0; 3; 0], max_list [2; 4; 6];;

(*renvoie la moyenne des nombres de la liste de flottants l.*)


let average l = 
  let rec aux l sum nb_element = match l, nb_element with 
  | [], 0. -> sum /. 1.
  | [], _  -> sum /. nb_element
  | h::t, _ -> aux t (sum +. h) (nb_element +. 1.)
  in aux l 0. 0.;;

  average [5.; 8.5; 11.5; 15.];;



(*renvoie le nombre de maximums de la liste l. Essayer de réaliser ce
calcul en un seul parcours. renvoi une exception si la liste entré est vide. *)

let nb_max l = 
  if l = [] then raise Empty_list
  else let rec aux l max nb_max = match l with
  | [] -> nb_max
  | h::t when h > max -> aux t h 1
  | h::t when h = max -> aux t max (nb_max+1)
  | h::t -> aux t max nb_max
  in aux l 0 0;;

  nb_max [1; 2; 3; 0; 3; 0], nb_max [2; 4; 6];;

let max a b = if a >= b then a else b;;

let min a b = if a <= b then a else b;;

(*teste si la longueur de la liste l est dans l’intervalle [a; b]
(ou [b; a])*)


  let size_in_range a b l = 
    let rec aux l size = 
      match l with 
      | []   -> size >= (min a b) && size <= (max a b)
      | _::l -> aux l (size+1)
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




let three_or_more_matched l = 
  let rec aux l acc = 
    match l, acc with 
    | [], _ -> acc 
    | _, 3 -> acc
    | _::l, _ -> aux l (acc+1)
  in aux l 0 >= 3;;

three_or_more_matched [0; 4];;

let list_copy l = 
  let rec aux l acc =
    match l with 
      [] -> acc
    | h::l -> aux l (h::acc)
  in List.rev (aux l [])


let l = [4; 5; 9];;
let l2 = list_copy l;;


let random_list n max = 
  let rec aux count acc = 
    let r = Random.int max in 
    match count with
  | n' when n' = n -> acc
  | _ -> aux (count+1) ([r] @ acc)
  in aux 0 [];;

let l = random_list 5 10;;

let reverse l = 
  let rec aux l acc =
    match l with 
      [] -> acc
    | h::l -> aux l (h::acc)
  in (aux l []);;

reverse l;;

let rec flatten_list l = 
  match l with 
  | [] -> []
  | h::t -> (flatten_list t) @ [h];;

  flatten_list [[1; 2]; []; [3; 4; 5]; [6]];;

let fibo n =
  let rec aux acc n2 n1 = function
  | 1 -> acc
  | c -> aux ((n2 + n1) :: acc) n1 (n2 + n1) (c - 1)
  in
  List.rev(aux [1; 0] 0 1 (n - 1))
;;

let fib n = 
  let rec aux acc acc2 i l = 
    match i with
    | n' when n' = n  -> l
    | n' -> aux acc2 (acc + acc2) (i+1) (l @ [acc])
    
  in aux 0 1 0 [];;


fib 9;;


let without_duplicates l = 

  let rec aux l buf acc = 
    match l with 
      [] -> acc
    | h::l when h <> buf -> aux l h (acc @ [h])
    | h::l -> aux l h acc 
  in aux l (List.hd l) [0];;

 without_duplicates [0; 0; 1; 2; 3; 3; 3; 3; 4; 5; 5; 6; 8; 8];;


let records l = 
  let rec aux l record acc = 
    match l with 
      [] -> acc
    | h::l when h >= record -> aux l h (acc @ [h])
    | h::l -> aux l record acc
  in aux l (hd l) [];;

  records [0; 2; 3; 2; 2; 6; 3; 2; 7; 4; 8; 4];;


let look_and_say n =
  let rec next c l e = match l with 
  | [] -> [c; e]
  | h::t when h = e -> next (c + 1) t h
  | h::t -> c::e::(next 1 t h) in 
  let rec aux n l acc = match n with 
  | v when v > 1 -> aux (n - 1) (next 1 (List.tl l) (List.hd l)) ([l]::acc)
  | _ -> acc in
  aux (n+1) [1] [];;

look_and_say 6;;

let f_split l = 
  let rec aux l i len acc acc2 = 
    match l, i with
      [], _ -> acc, acc2
    | h::l, n when n < (len/2) -> aux  l (i+1) len (acc @ [h]) acc2
    | h::l, n -> aux l (i+1) len acc (acc2 @ [h])
  in aux l 0 (size l) [] [];;



let l = random_list 20 100;;
let l1, l2 = f_split l;;


let f_merge l1 l2 = 
  let rec aux l1 l2 acc = 
    match l1, l2 with 
      [], [] -> acc
    (* Lorsque l'une des deux listes est vide mais pas l'autre, on ajoute la tête de l'autre liste à la liste accumulateur *)
    | [], h::l2 -> aux l1 l2 (acc @ [h])
    | h::l1, [] -> aux l1 l2 (acc @ [h])
    | h::l1, h'::l2 when h < h' -> aux l1 (h'::l2) (acc @ [h])
    | h::l1, h'::l2 -> aux (h::l1) l2 (acc @ [h'])
  in aux l1 l2 [];;

  let l1, l2 = (List.sort compare l1), (List.sort compare l2);;

  f_merge l1 l2;;

  let fusion_sort l = 
    let l1, l2 = f_split l in
      let l', l'' = (List.sort compare l1, List.sort compare l2) in
        f_merge l' l'';;
  
  fusion_sort l;;

let q_split l = 
  let pivot = hd l in 
    let rec aux l acc acc2 acc3 = 
      match l with
        [] -> acc, acc2, acc3
      | h::l when h < pivot -> aux l (acc @ [h]) acc2 acc3
      | h::l when h = pivot -> aux l acc (acc2 @ [h]) acc3
      | h::l -> aux l acc acc2 (acc3 @ [h])
    in aux l [] [] [];;


  let l1, l2, l3 = q_split l;;
  let l1, l2, l3 = (List.sort compare l1), l2, (List.sort compare l3);;

let q_merge l1 l2 l3 = 
    match l1, l2, l3 with
    | [], _, _ -> f_merge l2 l3
    | _, [], _ -> f_merge l1 l3
    | _, _, [] -> f_merge l1 l2
    | _, _, _ -> f_merge l1 (f_merge l2 l3);; 

q_merge l1 l2 l3;;



