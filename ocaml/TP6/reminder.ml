open List;;

type tree =
   |Leaf of int
   |Node of char * tree list


   let example_tree =
    Node ('a',
    [Node ('b', [Leaf 1; Leaf 2; Leaf 3]);
    Node ('c', [Node ('d', [Leaf 4; Leaf 5]); Node ('e', [Leaf 6])]);
    Leaf 7;
    Node ('f', [Node ('g', [Leaf 8]); Leaf 9])]);;



let rec tree_count_nodes t = 
  let rec count_node_list l = 
    match l with 
    | [] -> 0
    | h::tail -> match h with | Leaf _ -> 0 + count_node_list tail | Node (_, lst) -> 1 + count_node_list tail + count_node_list lst
  in match t with 
  | Leaf _ -> 0
  | Node (c, l) -> 1 + count_node_list l;;


tree_count_nodes example_tree;;

let tree_list_leaves t = 
  let rec aux lst acc = match lst with
  | [] -> acc
  | h::t -> match h with 
            | Leaf n -> n :: aux t acc 
            | Node (_, lst') -> (aux lst' acc) @ (aux t acc)
  in match t with 
  | Leaf n -> [n]
  | Node (c, l) -> aux l [];;

tree_list_leaves example_tree;;

