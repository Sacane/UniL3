(* point type definition *)
type point = float * float;;

(* Question 1 *)
(* float -> float -> point *)
(* make_point *)

let make_point abs ord : point = (abs, ord)
let x_of (p: point) : float = fst p
let y_of (p: point) : float = snd p;;

make_point 1.5 2.;;
make_point (-1.0) 2.5;;


(* Question 2 *)
(* point -> float *)
(* point_x *)

let x_of (p: point) : float = fst p
let y_of (p: point) : float = snd p;;
let p = make_point 1. 2.;;
x_of p;;
y_of p;;

(* point -> float *)
(* point_y *)


(* Question 3 *)
(* point -> point -> bool *)
(* point_domination *)


(* -------------------------------------------------------------------------- *)

(* rectangle type definition *)
type rectangle = point * point;;


(* Question 4 *)
(* point -> point -> rectangle *)
(* make_rectangle *)


(* Question 5 *)
(* rectangle -> point *)
(* rectangle_lower_left *)

(* rectangle -> point *)
(* rectangle_upper_right *)


(* Question 6 *)
(* rectangle -> float *)
(* rectangle_width *)

(* rectangle -> float *)
(* rectangle_height *)


(* Question 7 *)
(* rectangle -> point -> bool *)
(* rectangle_contains_point *)


(* Question 8 *)
(* rectangle -> point list -> point list *)
(* rectangle_contains_points *)


(* -------------------------------------------------------------------------- *)

(* quadtree type definition *)
type quadtree = | Leaf of point list * rectangle
                | Node of quadtree * quadtree * quadtree * quadtree * rectangle;;


(* Question 9 *)
(* rectangle -> rectangle * rectangle * rectangle * rectangle  *)
(* rectangle_split_four *)


(* Question 10 *)
(* ’a list -> ’a *)
(* smallest *)

(* ’a list -> ’a *)
(* largest *)


(* Question 11 *)
(* point list -> rectangle *)
(* enclosing_rectangle *)


(* Question 12 *)
(* point list -> int -> quadtree *)
(* quadtree_make *)


(* Question 13 *)
(* quadtree -> int  *)
(* quadtree_count *)


(* Question 14 *)
(* quadtree -> int list *)
(* quadtree_signature *)


(* -------------------------------------------------------------------------- *)


(* Question 15 *)
(* quadtree -> point list  *)
(* quadtree_all_points *)


(* rectangle -> rectangle -> bool *)
let rectangle_contains_rectangle r1 r2 =
    rectangle_contains_point r1 (rectangle_lower_left r2) &&
    rectangle_contains_point r1 (rectangle_upper_right r2);;

(* rectangle -> rectangle -> bool *)
let rectangle_disjoint (p1,p2) (p3,p4) =
    point_domination p3 p2 || point_domination p1 p4;;

(* rectangle -> rectangle -> rectangle *)
let rectangle_intersection ((p1,p2),(p3,p4))=
    let ll_x_max = largest [point_x p1; point_x p3] in
    let ll_y_max = largest [point_y p1; point_y p3] in
    let ur_x_min = smallest [point_x p2; point_x p4] in
    let ur_y_min = smallest [point_y p2; point_y p4] in
    let ll = make_point ll_x_max ll_y_max in
    let ur = make_point ur_x_min ur_y_min in
        make_rectangle ll ur;;


(* Question 16 *)
(* rectangle -> quadtree -> point list  *)
(* rectangle_query *)



(* -------------------------------------------------------------------------- *)

(* Question 17 *)
(* quadtree -> int -> point -> quadtree *)
(* quadtree_insert *)


(* Question 18 *)
(* quadtree -> point -> quadtree *)
(* quadtree_delete *)
