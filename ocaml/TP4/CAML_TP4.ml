let max a b = if a <= b then b else a;;

type bintree = 
  |Leaf
  |Node of bintree * int * bintree

type bintree_orientation = 
  |Left
  |Right

(*left side*)
let a = (Node (Leaf, 5, Leaf));;
let b = (Node (Leaf, 6, Leaf));;
let c = (Node (a, 6, b));;
let d = (Node (Leaf, 2, c));;


let e = (Node (Leaf, 2, Leaf));;

let f = (Node (e, 1, Leaf));;
let g = (Node (Leaf, 4, f));;


let tree = (Node (d, 2, g));;

let rec bitnree_count_nodes t = 
  match t with 
    Leaf -> 1
  | Node(left, _, right) -> 1 + (bitnree_count_nodes left) + (bitnree_count_nodes right);;

bitnree_count_nodes tree;;

let rec bintree_count_internal_nodes t = 
  match t with
  | Leaf -> 0
  | Node(left, _, right) -> 1 + (bintree_count_internal_nodes left) + (bintree_count_internal_nodes right);;

bintree_count_internal_nodes tree;;

let rec bintree_count_leaves t = 
  match t with 
    Leaf -> 1
  | Node (left, _, right) -> 0 + bintree_count_leaves left + bintree_count_leaves right;;

bintree_count_leaves tree;;

let rec bintree_count_right t = 
  match t with 
      Leaf -> 0
    | Node(left, _, right) when right <> Leaf -> 1 + bintree_count_right left + bintree_count_right right
    | Node(left, _, right) -> 0 + bintree_count_right left + bintree_count_right left;;


    bintree_count_right tree;;
    
let rec bintree_count_left t = 
  match t with 
      Leaf -> 0
    | Node(left, _, right) when left <> Leaf -> 1 + bintree_count_left left + bintree_count_right right
    | Node(left, _, right) -> 0 + bintree_count_left left + bintree_count_left right;;


bintree_count_left tree;;


let rec bintree_height t = 
  match t with 
  | Leaf -> 0
  | Node(left, _, right) -> 1 + max (bintree_height left) (bintree_height right);;

bintree_height tree;;


let rec bintree_is_mirror t1 t2 = 
  match t1, t2 with
  | Leaf, Leaf -> true
  | Leaf, Node(_, _, _) -> false
  | Node(_, _, _), Leaf -> false
  | Node(left, _, right), Node(left', _, right')
    -> bintree_is_mirror left right' && bintree_is_mirror left' right;;

bintree_is_mirror Leaf Leaf;;
    
bintree_is_mirror (Node(Leaf, 1, Leaf)) (Node(Leaf, 1, Leaf));;

bintree_is_mirror (Node(Leaf, 1, Node(Leaf, 3, Leaf))) (Node(Node(Leaf, 4, Leaf), 2, Leaf));;

let bintree_is_symetric = function
  | Leaf -> true
  | Node (left, _, right) -> bintree_is_mirror left right;;

  bintree_is_symetric Leaf;;

bintree_is_symetric (Node(Node(Leaf, 2, Leaf), 1, Node(Leaf, 3, Leaf)));;
bintree_is_symetric (Node(Node(Leaf, 2, Leaf), 1, Leaf));;

let bintree_collect_values t = 
  let rec aux t l = match t with 
    | Leaf -> l
    | Node(left, value, right) -> l @ [value] @ aux left l @ aux right l
  in aux t [];;


bintree_collect_values tree;;

let bintree_collect_level t depth = 
  let rec aux t l cpt = 
    match t, cpt with 
    | Leaf, _ -> l
    | Node(left, value, right), n when n = depth -> l @ [value] (* Case when we reached the given depth *)
    | Node(left, value, right), _ -> l @ aux left l (cpt+1) @ aux right l (cpt+1)
  in aux t [] 0;;

bintree_collect_level tree 0;;
bintree_collect_level tree 1;;
bintree_collect_level tree 2;;
bintree_collect_level tree 3;;
bintree_collect_level tree 4;;



let bintree_collect_canopy t = 
  let rec aux t l orientation =
    match t, orientation with
    | Leaf, Left -> l @ [0]
    | Leaf, Right -> l @ [1]
    | Node(left, value, right), _ -> l @ aux left l Left @ aux right l Right
  in aux t [] Left;;


bintree_collect_canopy tree;;

let bintree_visit_pre t = 
  let rec aux t l = match t with 
    | Leaf -> l
    | Node(left, value, right) -> l @ [value] @ aux left l @ aux right l
  in aux t [];;

bintree_visit_pre tree;;

let bintree_visit_post t =
  let rec aux t l = match t with 
  | Leaf -> l
  | Node (left, value, right) -> l @ aux left l @ aux right l @ [value]
  in aux t [];;

bintree_visit_post tree;;

let bintree_visit_in t = 
  let rec aux t l = match t with 
  | Leaf -> l 
  | Node(left, value, right) -> l @ aux left l @ [value] @ aux right l
  in aux t [];;

bintree_visit_in tree;;

let rec bintree_insert t value = 
  match t with 
  | Leaf -> Node(Leaf, value, Leaf)
  | Node(left, label, right) when label > value -> Node(bintree_insert left value, label, right)
  | Node(left, label, right) -> Node(left, label, bintree_insert right value);;

bintree_insert Leaf 1;;

bintree_insert (bintree_insert Leaf 1) 2;;

bintree_insert (bintree_insert (bintree_insert Leaf 1) 2) 3;;

bintree_insert (bintree_insert (bintree_insert Leaf 1) 2) 0;;

let is_bintree_search t = 
  let label_of_tree = function
  | Leaf -> 0
  | Node(_, value, _) -> value
  in
  let rec aux t tmp orientation = 
    match t, orientation with 
    | Leaf, _ -> true
    | Node(left, value, right), Left when value > tmp -> false
    | Node(left, value, right), Right when value < tmp -> false
    | Node(left, value, right), _ -> aux left value Left && aux right value Right
  in aux t (label_of_tree t) Left;;

  is_bintree_search tree;;

  is_bintree_search (Node(Leaf, 1, Node(Leaf, 10, Leaf)));;

 let rec binary_search t value = 
      match t with 
      | Leaf -> false
      | Node(left, label, right) when label = value -> true
      | Node(left, label, right) -> binary_search left value || binary_search right value;;

binary_search tree 5;;



let rec bintree_apply t  (apply : int -> int) = 
  match t with 
  | Leaf -> Leaf
  | Node(left, label, right) -> Node(bintree_apply left apply, apply label, bintree_apply right apply);;

  bintree_apply tree (function x -> x + 1);;

let rec bintree_double t = 
  bintree_apply t (function x -> x * 2);;

bintree_double tree;;

let rec bintree_rotate t = 
    match t with 
    | Leaf -> Leaf
    | Node(left, label, right) -> (Node(bintree_rotate right, label, bintree_rotate left))
    ;;

bintree_rotate tree;;

let bintree_sum_subtree t = 
  let rec sum_subtree = function
  | Leaf -> 0
  | Node(left, label, right) -> label + sum_subtree left + sum_subtree right in
  let rec sum t = match t with
  | Leaf -> Leaf
  | Node(left, label, right) -> Node(sum left, sum_subtree t, sum right) in
  sum t;;

bintree_sum_subtree tree;;
