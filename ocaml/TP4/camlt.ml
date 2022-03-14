let max a b = if a <= b then b else a;;

type bintree = 
  |Leaf
  |Node of bintree * int * bintree


(*left side*)
let a = (Node (Leaf, 5, Leaf));;
let b = (Node (Leaf, 6, Leaf));;
let c = (Node (a, 6, b));;
let d = (Node (Leaf, 2, c));;


let e = (Node (Leaf, 2, Leaf));;

let f = (Node (e, 1, Leaf));;
let g = (Node (Leaf, 4, f));;


let tree = (Node (d, 1, g));;

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
    when left <> Leaf && right' <> Leaf
    -> bintree_is_mirror left right' 
  | Node(left, _, right), Node(left', _, right') 
    when right <> Leaf && left' <> Leaf
    -> bintree_is_mirror right left'
  | Node(left, _, right), Node(left', _, right')
    -> bintree_is_mirror left left && bintree_is_mirror right right';;

bintree_is_mirror Leaf Leaf;;
    
bintree_is_mirror (Node(Leaf, 1, Leaf)) (Node(Leaf, 1, Leaf));;

bintree_is_mirror (Node(Leaf, 1, Node(Leaf, 3, Leaf))) (Node(Node(Leaf, 4, Leaf), 2, Leaf));;

let bintree_is_symetric = function
  | Leaf -> true
  | Node (left, _, right) -> bintree_is_mirror left right;;

  bintree_is_symetric Leaf;;

  bintree_is_symetric (Node(Node(Leaf, 2, Leaf), 1, Node(Leaf, 3, Leaf)));;