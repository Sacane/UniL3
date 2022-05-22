let interval (a: int) (b: int) = 
  List.init (b-a+1) (fun x -> x+a);;

interval 0 8;;
interval 2 5;;
interval 3 3;;
interval (-5) 2;;


let string_of_list l f = 
  List.fold_left (fun acc x -> acc ^ (f x)) "" l;;

string_of_list [0; 1; 2] string_of_int;;

string_of_list [] string_of_int;;



let compose_iter f x n = 
  let rec aux acc it = 
    if it = 0 then acc
    else aux (f acc) (it - 1) in 
  List.init (n+1) (aux x);;

compose_iter (fun x -> x + 1) 0 5;;

compose_iter (fun x -> -x) 8 6;;

let rec is_prefix_lists l1 l2 = 
  match l1, l2 with 
  | [], _ -> true
  | _, []  -> false
  | h::_, h'::_ when h <> h' -> false
  | h::t, h'::t' -> is_prefix_lists t t';;

is_prefix_lists [2; 1; 2; 3] [2; 1; 2; 3; 6; 2; 7];;

is_prefix_lists [] [2; 1; 2; 3];;

is_prefix_lists [2; 1] [];;

is_prefix_lists [] [];;

is_prefix_lists ['a'; 'b'; 'b'] ['a'; 'b'; 'b'];;


let rec is_factor_lists l1 l2 = 
  match l1, l2 with
  | [], _ -> true
  | _, [] -> false
  | l, h'::t' -> 
      if is_prefix_lists l (h'::t') then true
      else is_factor_lists l t'
;;

is_factor_lists [2; 1; 3] [4; 2; 1; 3; 4];;
is_factor_lists [2; 1; 3] [2; 1; 3; 4];;
is_factor_lists [2; 1; 3] [4; 2; 1; 3];;
is_factor_lists ['a'; 'a'] ['a'; 'b'; 'a'];;
is_factor_lists [] [];;


let rec is_subword_lists l1 l2 = 
  match l1, l2 with
  | [], _ -> true
  | _, [] -> false
  | h::t, h'::t' when h = h' -> is_subword_lists t t'
  | l, _::t' -> is_subword_lists l t'
;;

is_subword_lists [1; 3; 5] [1; 2; 3; 4; 5];;

is_subword_lists [1; 5; 3] [1; 2; 3; 4; 5];;

is_subword_lists ['a'; 'b'] ['a'; 'b'; 'c'];;

is_subword_lists [] ['a'];;
is_subword_lists [] [];;

let rec is_duplicate_free l = 
  let is_in l x = 
    List.exists (fun e -> e = x) l in
  match l with 
  | [] -> true
  | h::t -> 
    if is_in t h then false 
    else is_duplicate_free t;;


is_duplicate_free [1; 2; 3];;
is_duplicate_free [1; 2; 1];;
is_duplicate_free [1; 2; 1; 1; 2];;
is_duplicate_free [3];;
is_duplicate_free [];;
is_duplicate_free [1; 2; 3; 4; 5; 3];;

(*Exercice 2*)

(**********************************************************************)
(***************************** Exercice 2 *****************************)
(**********************************************************************)

type 'a automaton = {
    ribbon : int -> 'a;
    evol : 'a * 'a * 'a -> 'a;
    void : 'a
}

let create (f: 'a * 'a * 'a -> 'a) (v: 'a) = 
  {
    ribbon = (fun _ -> v);
    evol = f;
    void = v
  }
;;


let get_value aut n = 
  aut.ribbon n;;

  let aut1 = create (fun (a, b, c) -> a + b + c) 0;;

get_value aut1 0;;

get_value aut1 1024;;

let aut2 = create (fun (a, b, c) -> b) true;;

get_value aut2 (-2048);;

let set_value aut n value = 
  {aut with ribbon = (fun x -> if x = n then value else aut.ribbon x)}
;;

let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
let aut2 = set_value aut1 16 4;;
get_value aut2 16;;
get_value aut2 15;;
get_value aut1 16;;

type bunch = int * int


let get_bunch_values aut bun =
  let (a, b) = bun in  (* A NOTER*)
  let interval = (interval a b) in 
  List.map (fun x -> aut.ribbon x) interval;;


  let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
  let aut1 = set_value aut1 3 4;;


  let aut1 = set_value aut1 (-1) 2;;
  get_bunch_values aut1 (-2, 6);;


let to_string aut bun f = 
  let values = get_bunch_values aut bun in 
  string_of_list values f;;



to_string aut1 (-2, 6) string_of_int;;

let has_factor aut bun lst = 
  let values = get_bunch_values aut bun in 
  is_factor_lists lst values;;




has_factor aut1 (1, 8) [4; 0; 9; 0];;
has_factor aut1 (1, 5) [4; 0; 9; 0];;

let shift aut k = 
  {aut with ribbon = (fun x -> aut.ribbon (x + k))}
;;

let aut2 = shift aut1 3;;

to_string aut2 (-2, 6) string_of_int;;

let aut3 = shift aut1 (-4);;

to_string aut3 (-2, 6) string_of_int;;
to_string aut3 (-2, 12) string_of_int;;

let mirror aut = 
  {aut with ribbon = (fun x -> aut.ribbon (-x))};;

let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
  
let aut1 = set_value aut1 3 4;;

let aut1 = set_value aut1 (-1) 2;;

to_string aut1 (-8, 8) string_of_int;;

let map aut f = 
  {aut with ribbon = (fun x -> f (aut.ribbon x))};;

  let aut2 = map aut1 (fun x -> x + 1);;
  to_string aut2 (-8, 8) string_of_int;;