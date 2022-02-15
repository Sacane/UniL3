

(* Debug avec Begin end *)

let rec fact n = 
  if n = 0 then 1
  else n * (fact (n - 1));;

let n = fact 5;;

let rec fibo n = 
  if n = 0 then 0
  else if n = 1 then 1
  else fibo(n - 1) + fibo(n - 2);;

let n = fibo 7;;

(*let n = fibo 100;;*) 
(* Take too many times to answer *)

let rec pgcd m n = 
  if m = 0 then n
  else if m > n then pgcd n m
  else pgcd(n mod m) m;;

pgcd;;

pgcd 1 1;;

pgcd 20 30;;

pgcd 77 34;;





let rec ack m n = 
  match (m, n) with 
  (0, _) -> n + 1
  | (_, 0) -> ack (m-1) 1
  | (_, _) -> ack (m-1) (ack m (n-1));;


  ack;;

  ack 0 1, ack 1 1, ack 2 1, ack 3 1;;
  
  ack 0 2, ack 1 2, ack 2 2, ack 3 2;;

  
