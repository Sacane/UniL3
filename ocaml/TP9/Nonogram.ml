(**********************************************************************)
(***************************** Exercise 1 *****************************)
(**********************************************************************)

(* 1.1. *)
(* val interval : int -> int -> int list = <fun> *)

let interval min max = 
    let rec aux acc value = 
        if value > max then List.rev acc
        else aux (value::acc) (value+1)
    in aux [] min;;

interval 0 8
;;

interval 2 5;;
interval 3 3;;



(* 1.2. *)
(* val interval_f : int -> int -> (int -> 'a) -> 'a list = <fun> *)

let interval_f a b (f: int -> int) = 
    List.rev (List.fold_left (fun acc x -> (f x :: acc)) [] (interval a b));;

interval_f 2 8 (fun x -> 2 * x);;

(* 1.3. *)
(* val is_positive_list : int list -> bool = <fun> *)

let is_positive_list lst = 
    List.fold_left (fun acc x -> if x > 0 then acc else false) true lst;;

is_positive_list [3; 1; 1; 2];;
is_positive_list [3; 1; 0; 2];;
is_positive_list [3; (-1); 1; 2];;



(* 1.4. *)
(* val is_sum_leq_list : int list -> int -> bool = <fun> *)

let is_sum_leq_list lst n = 
    (List.fold_left (+) 0 lst) <= n;;

is_sum_leq_list [0; 1; 2] 25;;
is_sum_leq_list [0; 1; 2] 3;;
is_sum_leq_list [0; 1; 2] 2;;

(* 1.5. *)
(* val are_equivalent_lists : 'a list -> 'b list -> ('a -> 'b -> bool)
        -> bool = <fun> *)

let rec are_equivalent_lists lst lst2 f = 
    match lst, lst2 with
    |   _::_, [] -> false
    |   [], _::_ -> false
    |   [], [] -> true
    |   h::t, h'::t' when (f h h') = false -> false
    |   _::t, _::t' -> are_equivalent_lists t t' f
;;

are_equivalent_lists [1; 2; 3] [1; 2; 3] (=);;

are_equivalent_lists [0; 0; 1] [0; 0] (=);;


     

(**********************************************************************)
(***************************** Exercise 2 *****************************)
(**********************************************************************)

(* Given type. *)
type state = Empty | Black

(* Given type. *)
type square = int * int

(* Given type. *)
type grid = {
    nb_rows : int;
    nb_columns : int;
    states : square -> state
}

(* Given function. *)
let state_to_string c =
    match c with
        |Empty -> "-"
        |Black -> "O"

(* Given function. *)
let grid_to_string grid =
    let index_rows = interval 1 grid.nb_rows
    and index_columns = interval 1 grid.nb_columns in
    List.fold_left
        (fun res i ->
            let line = List.fold_left
                (fun res j ->
                    res ^ (state_to_string (grid.states (i, j))) ^ "|")
                "|"
                index_columns
            in
            res ^ line ^ "\n")
        ""
        index_rows

(* 2.1. *)
(* val empty_grid : int -> int -> grid = <fun> *)



let empty_grid x y = 
    {
        nb_rows = x;
        nb_columns = y;
        states = (fun _ -> Empty)
    }
;;

print_string (grid_to_string (empty_grid 5 3));;

(* 2.2 *)
(* val fill_square : grid -> square -> grid = <fun> *)

let fill_square g s = 
    let x, y = s in 
    if x > g.nb_rows || y > g.nb_columns then g else 
    {
        g with states = 
        (fun s' -> if s' = s then Black else g.states s')
    };;


let g = empty_grid 5 3;;
let g = fill_square g (1, 1);;
let g = fill_square g (5, 3);;

print_string (grid_to_string g);;

(* 2.3. *)
(* val fill_squares : grid -> square list -> grid = <fun> *)

let rec fill_squares g lst = 
    match lst with
    |[] -> g
    |h::t -> fill_squares (fill_square g h) t;;

print_string (grid_to_string (fill_squares (empty_grid 4 3) []));;
print_string (grid_to_string (fill_squares (empty_grid 4 3) [(1, 2); (1, 3); (4, 3)]));;

(* 2.4. *)
(* val row : grid -> int -> state list = <fun> *)

let row g n = 
    if n > g.nb_rows then [] else 
    List.init g.nb_columns (fun i -> g.states (n, (i+1)));;


let g = fill_squares (empty_grid 5 3)
[(1, 1); (1, 2); (1, 3); (3, 1); (3, 3); (4, 3)];;




print_string (grid_to_string g);;

row g 1;;

row g 3;;

row g 4;;

row g 5;;
    

    

(* 2.5. *)
(* val column : grid -> int -> state list = <fun> *)

let column g n = 
    if n > g.nb_columns then [] else 
    List.init g.nb_rows (fun i -> g.states ((i+1), n));;

let g = fill_squares (empty_grid 5 3)
[(1, 1); (1, 2); (1, 3); (3, 1); (3, 3); (4, 3)];;

column g 1;;
column g 3;;
column g 4;;

(**********************************************************************)
(***************************** Exercise 3 *****************************)
(**********************************************************************)

(* Given type. *)
type profile = int list

(* 3.1. *)
(* val profile : state list -> profile = <fun> *)

let profile lst = 
    let rec aux lst acc cpt = 
        match lst with 
        |   [] when cpt <> 0 -> acc @ [cpt]
        |   [] -> List.rev acc
        |   Empty::t when cpt = 0 -> aux t acc 0 
        |   Empty::t -> aux t ([cpt] @ acc) 0
        |   Black::t -> aux t acc (cpt+1)
    in aux lst [] 0;;

profile [Black; Black];;

profile [Black; Black; Empty];;

profile [Empty; Black; Black; Empty];;

profile [Empty; Black; Empty; Empty; Black; Black; Empty];;

profile [];;


(* 3.2. *)
(* val are_profiles_compatible : profile -> profile -> bool = <fun> *)

let rec are_profiles_compatible p p' = 
    match p, p' with 
    |   [], _ -> true
    |   _::_, [] -> false
    |   h::t, h'::t' when h <= h' -> 
        let x = h' - h - 1 in 
            if x <= 0 then are_profiles_compatible t t'
            else are_profiles_compatible t (x :: t')
    |   h::t, h'::t' -> are_profiles_compatible p (t');;
            
    

are_profiles_compatible [] [];;
are_profiles_compatible [] [1; 3; 1; 2];;
are_profiles_compatible [1] [];;
are_profiles_compatible [1] [1; 3; 1; 2];;
are_profiles_compatible [1; 2] [1; 3; 1; 2];;
are_profiles_compatible [1; 4] [1; 3; 1; 2];;
are_profiles_compatible [3] [1; 3; 1; 2];;
are_profiles_compatible [] [];;
are_profiles_compatible [4] [1; 3; 1; 2];;
are_profiles_compatible [1; 2; 3] [1; 4; 4];;


(**********************************************************************)
(***************************** Exercise 4 *****************************)
(**********************************************************************)

(* Given type. *)
type spec = {
    rows : profile list;
    columns : profile list
}

(* 4.1. *)
(* val dimensions_spec : spec -> int * int = <fun> *)
let dimensions_spec sp = 
    (List.length sp.rows, List.length sp.columns);;

dimensions_spec {rows = [[3]; [2]; [1; 1]; [2]; [3]; [1; 1]];
columns = [[1; 1; 2] ; [1; 2]; [6]; [1]]};;

(* 4.2. *)
(* val is_solution : spec -> grid -> bool = <fun> *)



(**********************************************************************)
(***************************** Exercise 5 *****************************)
(**********************************************************************)

(* 5.1. *)
(* val next_square : grid -> square -> square = <fun> *)

(* 5.2. *)
(* val is_square : grid -> square -> bool = <fun> *)

(* 5.3. *)
(* val solve_brute_force : spec -> bool * grid = <fun> *)

(* 1.6 *)
(* val cartesian_product_lists : 'a list -> 'b list -> ('a * 'b) list
        = <fun> *)

