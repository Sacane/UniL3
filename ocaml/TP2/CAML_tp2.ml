#use "../TP1/CAML_tp1.ml"

let rec fact n = 
  if n = 0 then 1
  else n * (fact (n - 1));;

let n = fact 5;;

let exp x n = 
  let rec aux x n acc nbCall= 
    if n = 0 then acc, nbCall
    else aux (x) (n-1) (acc * x) (nbCall+1)
  in aux x n 1 0;;

  let rec fib n = 
    if n = 0 then 0
    else if n = 1 then 1
    else fib(n - 1) + fib(n - 2);;
  
  
fib 0, fib 1, fib 2, fib 3, fib 4, fib 5;;


let rec pgcd m n = 
  if m = 0 then n
  else if m > n then pgcd n m
  else pgcd(n mod m) m;;

pgcd;;

pgcd 1 1;;

pgcd 20 30;;

pgcd 77 34;;

let rec ackerman m n = 
  match (m, n) with 
  (0, _) -> n + 1
  | (_, 0) -> ackerman (m-1) 1
  | (_, _) -> ackerman (m-1) (ackerman m (n-1));;


ackerman;;

ackerman 0 1, ackerman 1 1, ackerman 2 1, ackerman 3 1;;

ackerman 0 2, ackerman 1 2, ackerman 2 2, ackerman 3 2;;



let rec binom n k = 
  match (n, k) with
  (_, 0) -> 1
  | (n, k) when n < k -> 0
  | (n, k) -> binom (n - 1) (k - 1) + binom (n - 1) k;;

binom 0 0;;

binom 1 0, binom 1 1;;

binom 2 0, binom 2 1, binom 2 2;;


let binom2 n k = 
  fact(n) / (fact(k) * fact(n - k));;

let compareBinom = binom2 2 0;;
let compareBinom2 = binom 2 0;;

let check_binom_versions = 
  let rec check_binom_bis n k = 
    let compare = binom n k = binom2 n k in 
      if n > 3 then true
      else if k < n then 
        if compare <> true then 
          false
        else 
          check_binom_bis n (k+1)
      else 
        if n <= 3 then check_binom_bis (n+1) 0
        else false
      in check_binom_bis 0 0;;
    
          
let rec is_even n = 
  if n = 0 || is_odd (n-1) = true then true else false 
  and is_odd n = 
    if n <> 0 = true && is_even (n - 1) = true then true
    else false;;

let fact' n =
  let rec aux n acc = 
    if n = 0 then acc
    else aux (n - 1) (n * acc)
  in aux n 1;;

print_string("FACT");;
fact, fact';;
fact 0 = fact' 0, fact 1 = fact' 1, fact 2 = fact' 2, fact 10 = fact' 10;;






(*  let rec fib n = 
    if n = 0 then 0
    else if n = 1 then 1
    else fib(n - 1) + fib(n - 2);;
  *)

let fib' n = 
  let rec aux n acc acc2 = 
    if n = 0 then acc
    else aux (n - 1) (acc2) (acc + acc2)
  in aux n 0 1;;

fib 0 = fib' 0, fib 1 = fib' 1, fib 2 = fib' 2, fib 10 = fib' 10, fib 4 = fib' 4;;


let syracuse n = 
  let rec aux n acc = 
    if n = 1 then acc
    else
      if is_even(n) then aux (n / 2) (acc + 1)
      else aux (n * 3 + 1) (acc + 1)
  in aux n 0;;


syracuse 17;;
syracuse 100;;






let exp' x n = 
  let rec aux x n acc = 
    if n = 0 then acc
    else aux (x) (n-1) (acc * x)
    
  in aux x n 1;;

let rec fast_exp x n= 
  if n = 0 then 1
  else if n mod 2 = 0 then
    let tmp = fast_exp x (n/2)
    in tmp * tmp
  else x * fast_exp x (n-1);;

let fast_exp x n = 
  let rec aux x n acc = 
    if n = 0 then 1, acc
    else if n mod 2 = 0 then
      let tmp = fst (aux x (n / 2) (acc + 1))
      in tmp * tmp, acc
    else x * fst (aux x (n - 1) (acc + 1)), acc
  in aux x n 0;;


let sum1 n m = 
  let rec aux1 n m acc = 
    if n < m then aux1 (n+1) m (n + acc)
    else 
    
    
