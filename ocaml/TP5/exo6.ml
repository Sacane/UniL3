type bintree = Leaf | Node of int * bintree * bintree;;

let example_tree =
Node(1,
Node(2,
Node(4, Leaf, Leaf),
Node(5, Node(7, Leaf, Leaf), Node(8, Leaf, Leaf))),
Node(3, Leaf, Node(6, Node(9, Leaf, Leaf), Leaf)));;


let rec map_tree (f : 'a -> 'b) t = match t with 
  	| Leaf -> Leaf
    | Node(v, left, right) -> Node(f v, map_tree f left, map_tree f right);;

map_tree (fun x -> x * 2) example_tree;;


let rec fold_tree op t (seed : 'a) = 
  match t with 
  | Leaf -> seed
  | Node(v, left, right) -> op v (fold_tree op left seed) (fold_tree op right seed);;

let rec bintree_count_internal_nodes t = fold_tree (fun v l r -> 1 + l + r) t 0;;

let rec bintree_collect_internal_nodes t = fold_tree (fun v l r -> [v] @ r @ l) t [];;

bintree_count_internal_nodes example_tree;;

bintree_collect_internal_nodes example_tree;;

map_tree (fun x -> x*3) example_tree;;