type point = float * float;;
exception Not_good_value 

type rectangle = point * point;;

let make_point abs ord : point = (abs, ord)
let x_of (p: point) : float = fst p
let y_of (p: point) : float = snd p;;

make_point 1.5 2.;;
make_point (-1.0) 2.5;;



let p = make_point 1. 2.;;
x_of p;;
y_of p;;

let point_domination (p1: point) (p2: point) : bool = 
  (x_of p1) >= (x_of p2) && (y_of p1) >= (y_of p2)
  ;;

let p1 = make_point 0. 0. and p2 = make_point 0. 1. and p3 = make_point 1. 1.;;

point_domination p1 p1, point_domination p1 p2, point_domination p1 p3;;
point_domination p2 p1, point_domination p2 p2, point_domination p2 p3;;
point_domination p3 p1, point_domination p3 p2, point_domination p3 p3;;

let make_rectangle (p1: point) (p2: point) : rectangle = (p1, p2)



let p1 = make_point 0. 0. and p2 = make_point 1. 2.;;
make_rectangle p1 p2;;


let rectangle_lower_left r : point = 
  fst (r)

let rectangle_upper_right r : point = 
  snd (r)


let r = make_rectangle (make_point 0. 0.) (make_point 1. 2.);;

rectangle_lower_left r;;

rectangle_upper_right r;;

let rectangle_width (r: rectangle) : float =
  (x_of (rectangle_upper_right r) -. x_of (rectangle_lower_left r))

let rectangle_height (r: rectangle) : float =
  (y_of (rectangle_upper_right r) -. y_of (rectangle_lower_left r))
  ;;

rectangle_width r;;

rectangle_height r;;

let rectangle_contains_point (r: rectangle) (p: point) : bool = 
  point_domination (rectangle_upper_right r) p && point_domination p (rectangle_lower_left r)
  ;;

let r = make_rectangle (make_point 0. 0.) (make_point 1. 1.);;
let p1 = make_point 0. 0.;;

let p1 = make_point 0. 0.
and p2 = make_point 0.5 0.5
and p3 = make_point 0.5 1.5;;

rectangle_contains_point r p1;;
rectangle_contains_point r p2;;
rectangle_contains_point r p3;;

let rectangle_contained_points (r: rectangle) (plist : point list) : point list = 
  List.filter (fun x -> rectangle_contains_point r x) plist;;

let r = make_rectangle (make_point 0. 0.) (make_point 1. 1.);;


let p1 = make_point 0. 0.
and p2 = make_point 0.5 0.5
and p3 = make_point 0.5 1.5;;

rectangle_contained_points r [p1; p2; p3];;


(* -------------------------------------------------------------------------- *)

(* quadtree type definition *)
type quadtree = | Leaf of point list * rectangle
                | Node of quadtree * quadtree * quadtree * quadtree * rectangle;;


(* Question 9 *)
(* rectangle -> rectangle * rectangle * rectangle * rectangle  *)
(* rectangle_split_four *)


let rectangle_split_four (r : rectangle) : rectangle * rectangle * rectangle * rectangle = 
  let upper_left =
    make_rectangle 
      (make_point (x_of (rectangle_lower_left r)) (y_of (rectangle_upper_right r) /. 2.))
      (make_point (x_of (rectangle_upper_right r) /. 2.) (y_of(rectangle_upper_right r)))

  and upper_right = 
    make_rectangle 
      (make_point 
        (x_of (rectangle_upper_right r) /. 2.) 
        (y_of (rectangle_upper_right r) /. 2.))
      (rectangle_upper_right r)

  and lower_left = 
    make_rectangle 
      (rectangle_lower_left r)
      (make_point 
        (x_of (rectangle_upper_right r) /. 2.) 
        (y_of(rectangle_upper_right r) /. 2.))

  and lower_right = 
    make_rectangle 
      (make_point 
        (x_of (rectangle_upper_right r) /. 2.)
        (y_of (rectangle_lower_left r)))
      (make_point
        (x_of (rectangle_upper_right r))
        (y_of (rectangle_upper_right r) /. 2.))

  in (upper_left, upper_right, lower_right, lower_left)

let r_splited = make_rectangle (make_point 0. 0.) (make_point 1. 2.);;
rectangle_split_four r;;

(* Question 10 *)
(* ’a list -> ’a *)
(* smallest *)

let smallest (l: 'a list) : 'a =
  List.fold_left (fun acc x -> if compare x acc < 0 then x else acc) (List.hd l) l
  

(* ’a list -> ’a *)
(* largest *)



let largest (l: 'a list) : 'a = 
  List.fold_left (fun acc x -> if compare x acc > 0 then x else acc) (List.hd l) l


let l = [2; 4; 6; 1; 8; 4; 3; 1];;
smallest l;;
largest l;;


(* Question 11 *)
(* point list -> rectangle *)
(* enclosing_rectangle *)

let enclosing_rectangle (plist: point list) : rectangle =
  let x_list = List.map (fun p -> x_of p) plist
  and y_list = List.map (fun p -> y_of p) plist in
    let x_min = smallest x_list
    and x_max = largest x_list
    and y_min = smallest y_list
    and y_max = largest y_list in
      let p_lower_left = make_point x_min y_min
      and p_upper_right = make_point x_max y_max
        in make_rectangle p_lower_left p_upper_right

let p1 = make_point 0. 0. and p2 = make_point 0.5 0.5 and p3 = make_point 0.5 1.5;;
enclosing_rectangle [p1; p2; p3];;


(* Question 12 *)
(* point list -> int -> quadtree *)
(* quadtree_make *)

let quadtree_make (plist: point list) (n: int) : quadtree = 
  let rec aux_make plist rectangle = 
    if List.length plist <= n then Leaf (plist, rectangle)
    else
      let nw, ne, se, sw = rectangle_split_four rectangle in
      Node (
        aux_make (rectangle_contained_points nw plist) nw, 
        aux_make (rectangle_contained_points ne plist) ne,
        aux_make (rectangle_contained_points se plist) se,
        aux_make (rectangle_contained_points sw plist) sw,
        rectangle
      )
  in aux_make plist (enclosing_rectangle plist);;
    
  let p1 = make_point 0. 0.
  and p2 = make_point 0.5 0.5
  and p3 = make_point 0.5 1.5;;
  quadtree_make [p1; p2; p3] 1;;

(* Question 13 *)
(* quadtree -> int  *)
(* quadtree_count *)


(* Question 14 *)
(* quadtree -> int list *)
(* quadtree_signature *)


(* -------------------------------------------------------------------------- *)

(*TODO*)


(* -------------------------------------------------------------------------- *)

(* Question 17 *)
(* quadtree -> int -> point -> quadtree *)
(* quadtree_insert *)


(* Question 18 *)
(* quadtree -> point -> quadtree *)
(* quadtree_delete *)
