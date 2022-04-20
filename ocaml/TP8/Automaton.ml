(**********************************************************************)
(***************************** Exercice 1 *****************************)
(**********************************************************************)

(* 1.1. *)
(* val interval : int -> int -> int list = <fun> *)

let interval a b = 
    let rec aux acc value = 
        if value > b then List.rev acc
        else aux (value::acc) (value+1)
    in aux [] a;;

interval 0 8;;

(* 1.2. *)
(* val string_of_list : 'a list -> ('a -> string) -> string = <fun> *)

let string_of_list lst f = 
    List.fold_left (fun acc x ->  acc ^ f x) "" lst;;

string_of_list [0; 1; 2] string_of_int;;

(* 1.3. *)
(* val compose_iter : ('a -> 'a) -> 'a -> int -> 'a list = <fun> *)

let compose_iter f x n = 
    let rec aux acc it = 
        if it = 0 then acc
        else aux (f acc) (it - 1)
    in List.init (n + 1) (fun i -> aux x i)
;;



compose_iter (fun x -> x + 1) 0 5;;
compose_iter (fun x -> -x) 8 6;;
compose_iter (fun u -> u ^ "a") "b" 5;;


(* 1.4. *)
(* val is_prefix_lists : 'a list -> 'a list -> bool = <fun> *)

let rec is_prefix_lists lst1 lst2 = 
    match lst1, lst2 with
    |[], [] -> true
    |[], _ -> true
    |_, []  -> false
    |h::t, h'::t' when h = h' -> is_prefix_lists t t'
    |h::t, h'::t' -> false
    ;;
    
is_prefix_lists [2; 1; 2; 3] [2; 1; 2; 3; 6; 2; 7];;
is_prefix_lists [] [2; 1; 2; 3];;
is_prefix_lists [2; 1] [];;
is_prefix_lists [2; 1; 3] [2; 1; 2; 3; 6; 2; 7];;
is_prefix_lists ['a'; 'b'; 'b'] ['a'; 'b'; 'b'];;


(* 1.5. *)
(* val is_factor_lists : 'a list -> 'a list -> bool = <fun> *)

(**
        if p_left = [] then true 
        else if l_left = [] then p_left = []
        else if (List.hd p_left) = (List.hd l_left) then aux (List.tl p_left) (List.tl l_left)
        else aux lst1 (List.tl l_left)
*)

let rec is_factor_lists lst1 lst2 = 
    if List.length lst2 < List.length lst1 then false
    else if is_prefix_lists lst1 lst2 then true
    else is_factor_lists lst1 (List.tl lst2);;



is_factor_lists [2; 1; 3] [2; 1; 3; 4];;
is_factor_lists [2; 1; 3] [4; 2; 1; 3; 4];;
is_factor_lists ['a'; 'a'] ['a'; 'b'; 'a'];;




(* 1.6. *)
(* val is_subword_lists : 'a list -> 'a list -> bool = <fun> *)

let is_subword_lists lst1 lst2 = 
    let rec aux l1 l2 = 
        match l1, l2 with 
        |   [], [] -> true
        |   [], _ -> true
        |   _, [] -> false
        |   h::t, h'::t' when h = h' -> aux t t'
        |   h::t, h'::t' -> aux (h::t) t'
    in aux lst1 lst2;;

is_subword_lists [1; 3; 5] [1; 2; 3; 4; 5];;
is_subword_lists [1; 5; 3] [1; 2; 3; 4; 5];;
is_subword_lists [] ['a'];;

(* 1.7. *)
(* val is_duplicate_free : 'a list -> bool = <fun> *)

let rec is_duplicate_free lst = 
    match lst with 
    |   [] -> true
    |   h::t when List.exists (fun x -> x = h) t -> false 
    |   h::t -> is_duplicate_free t
    ;;

is_duplicate_free [1; 2; 3];;
is_duplicate_free [1; 2; 1];;
is_subword_lists ['a'; 'b'] ['a'; 'b'; 'c'];;
is_subword_lists [] ['a'];;

(**********************************************************************)
(***************************** Exercice 2 *****************************)
(**********************************************************************)

type 'a automaton = {
    ribbon : int -> 'a;
    evol : 'a * 'a * 'a -> 'a;
    void : 'a
}

(* 2.1. *)
(* val create : ('a * 'a * 'a -> 'a) -> 'a -> 'a automaton = <fun> *)

let create (f: 'a * 'a * 'a -> 'a) (v: 'a) = 
    {
        ribbon = (fun _ -> v);
        evol = f;
        void = v
    };;

create (fun (a, b, c) -> a + b + c) 0;;

create (fun (a, b, c) -> b) true;;
(* 2.2. *)
(* val get_value : 'a automaton -> int -> 'a = <fun> *)

let get_value aut n = 
    aut.ribbon n
    ;;

let aut1 = create (fun (a, b, c) -> a + b + c) 0;;

get_value aut1 0;;
get_value aut1 1024;;

let aut2 = create (fun (a, b, c) -> b) true;;

get_value aut2 (-2038)

(* 2.3. *)
(* val set_value : 'a automaton -> int -> 'a -> 'a automaton = <fun> *)

let set_value aut n value = 
    {
        ribbon = (fun i -> if i = n then value else aut.ribbon i);
        evol = aut.evol;    
        void = aut.void
    }


let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
let aut2 = set_value aut1 16 4;;
get_value aut2 15;;
get_value aut2 16;;
get_value aut1 16;;


(**********************************************************************)
(***************************** Exercice 3 *****************************)
(**********************************************************************)

type bunch = int * int



(* 3.1. *)
(* val get_bunch_values : 'a automaton -> bunch -> 'a list = <fun> *)

let get_bunch_values aut bun = 
    let (a, b) = bun in
    let interval = interval a b in 
    List.map (fun idx -> aut.ribbon idx) interval
    ;;


let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
let aut1 = set_value aut1 3 4;;
let aut1 = set_value aut1 (-1) 2;;
get_bunch_values aut1 (-2, 6);;

(* 3.2. *)
(* val to_string : 'a automaton -> bunch -> ('a -> string) -> string
    = <fun> *)

let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
let aut1 = set_value aut1 3 4;;
let aut1 = set_value aut1 (-1) 2;;

let to_string aut bun f = 
    let values = get_bunch_values aut bun in
    string_of_list values f;;

to_string aut1 (-2, 6) string_of_int;;
to_string aut1 (-2, 6) (fun x -> if x = 0 then "." else "*");;


(* 3.3. *)
(* val has_factor : 'a automaton -> bunch -> 'a list -> bool = <fun> *)

let has_factor aut bun lst = 
    let values = get_bunch_values aut bun in 
    is_factor_lists lst values;;

let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
let aut1 = set_value aut1 3 4;;
let aut1 = set_value aut1 (-1) 2;;
let aut1 = set_value aut1 5 9;;
has_factor aut1 (1, 8) [4; 0; 9; 0];;
has_factor aut1 (1, 5) [4; 0; 9; 0];;


(* 3.4. *)
(* val has_subword : 'a automaton -> bunch -> 'a list -> bool = <fun> *)

let has_subword aut bun lst = 
    let values = get_bunch_values aut bun in 
    is_subword_lists lst values;;

let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
let aut1 = set_value aut1 3 4;;
let aut1 = set_value aut1 (-1) 2;;
let aut1 = set_value aut1 5 9;;
has_subword aut1 (1, 8) [4; 9];;
has_subword aut1 (7, 8) [4; 9];;


(**********************************************************************)
(***************************** Exercice 4 *****************************)
(**********************************************************************)

(* 4.1. *)
(* val shift : 'a automaton -> int -> 'a automaton = <fun> *)

let shift aut k = 
    {aut with ribbon = (fun i -> aut.ribbon (i + k));}
    
let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
let aut1 = set_value aut1 3 4;;
let aut1 = set_value aut1 (-1) 2;;

to_string aut1 (-2, 6) string_of_int;;

let aut2 = shift aut1 3;;
to_string aut2 (-2, 6) string_of_int;;
let aut3 = shift aut1 (-4);;
to_string aut3 (-2, 6) string_of_int;;



(* 4.2. *)
(* val mirror : 'a automaton -> 'a automaton = <fun> *)

let mirror aut = 
    {aut with ribbon = (fun i -> (-i));}

let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
let aut1 = set_value aut1 3 4;;
let aut1 = set_value aut1 (-1) 2;;

to_string aut1 (-8, 8) string_of_int;;
let aut2 = shift aut1 3;;
to_string aut2 (-2, 6) string_of_int;;
let aut3 = shift aut1 (-4);;
to_string aut3 (-2, 6) string_of_int;;


(* 4.3. *)
(* val map : 'a automaton -> ('a -> 'a) -> 'a automaton = <fun> *)

let map aut f = 
    {aut with ribbon = (fun i -> f (aut.ribbon i));}

let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
let aut1 = set_value aut1 3 4;;
let aut1 = set_value aut1 (-1) 2;;

to_string aut1 (-8, 8) string_of_int;;
let aut2 = map aut1 (fun x -> x + 1);;

to_string aut2 (-8, 8) string_of_int;;

(* 4.4. *)
(* val evolution : 'a automaton -> 'a automaton = <fun> *)

let evolution aut = 
    {aut with ribbon = (fun i -> aut.evol ((aut.ribbon (i-1)), (aut.ribbon i), (aut.ribbon (i+1))))}

let aut1 = create (fun (a, b, c) -> a + b + c) 0;;
let aut1 = set_value aut1 3 4;;
let aut1 = set_value aut1 2 1;;
let aut1 = set_value aut1 (-1) 2;;


to_string aut1 (-8, 8) string_of_int;;
let aut2 = evolution aut1;;
to_string aut2 (-8, 8) string_of_int;;
(* 4.5. *)
(* val evolutions : 'a automaton -> int -> 'a automaton list = <fun> *)

let evolutions aut n = 
    let rec iter i acc = 
        match i with 
        |   k when k = n -> acc
        |   _ -> iter (i+1) ([evolution aut] @ acc)
    in iter 0 [];;

let aut = create (fun (a, b, c) -> a + b) 0;;

let aut = set_value aut 0 1;;

let lst = evolutions aut 4;;

(* 4.6. *)
(* val evolutions_bunch : 'a automaton -> bunch -> int -> 'a list list
    = <fun> *)

(* 4.7. *)
(* val is_resurgent : 'a automaton -> bunch -> int -> bool *)

(**********************************************************************)
(***************************** Exercice 5 *****************************)
(**********************************************************************)

(* 5.1. *)
(* val sierpinski : int automaton
    = {ribbon = <fun>; evol = <fun>; void = 0} *)

(* 5.2. *)
(* Type wb. *)
(* val chaos : wb automaton
    = {ribbon = <fun>; evol = <fun>; void = White} *)

(**********************************************************************)
(***************************** Exercice 6 *****************************)
(**********************************************************************)

(* 6.1. *)

(* 6.2. *)
