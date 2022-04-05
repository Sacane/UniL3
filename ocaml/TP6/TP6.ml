#load "graphics.cma";;

#use "topfind";;
#require "graphics";;

open Graphics;;

(* Dimensions of the graphical window. *)
let w = 512 and h = 512

(* Type for the representation of functional images. *)
type picture  = int * int -> Graphics.color

(* render f : draw the image `f` on the graphical window. *)
let render (f : picture) =
    open_graph (Printf.sprintf " %dx%d" w h);
    auto_synchronize false;
    for x = 0 to w - 1 do
        for y = 0 to h - 1 do
            set_color (f (x, y));
            plot x y
        done;
        set_color background
    done;
    synchronize ();
    (wait_next_event [Button_down; Key_pressed]) |> ignore;
    close_graph ()

let from_polar (rho, theta) =
    (int_of_float (rho *. cos theta), int_of_float (rho *. sin theta)) 

let to_polar (x, y) =
    let distance_to_origin (x, y) = sqrt (float_of_int (x * x + y * y)) in
    (distance_to_origin (x, y), atan2 (float_of_int y) (float_of_int x))

let black_on_black : picture = fun point -> black;;
let half_plane color : picture = 
    fun (x, y) -> if x < w /2 then color else background;;

(*(render (half_plane black));;*)



let diagonal (color: Graphics.color) = 
  fun (x, y) -> if x = y then color else background;;



(*render (diagonal black);;*)

let square side_size (color: Graphics.color) = fun (x, y) ->
  if x >= (h/2) - (side_size/2) && x <= (h/2) + (side_size / 2) 
  && y >= (w/2) - (side_size / 2) && y <= (w/2) + (side_size / 2) then color
  else background;;



(*render (square 90 red);;*)

let rectangle side_x side_y (color: Graphics.color) = 
  fun (x, y) ->
  if x >= (h/2) - (side_x/2) && x <= (h/2) + (side_x / 2) 
  && y >= (w/2) - (side_y / 2) && y <= (w/2) + (side_y / 2) then color
  else background;;

(*render (rectangle 90 54 red);;*)

let disk radius color = 
  
  let center = (h/2, w/2) and 
  pow x = x * x in 
  fun (x, y) -> 
  if sqrt (float_of_int (pow (y - snd center) + pow (x - fst center))) <= float_of_int radius then color 
  else background;;

(*render (disk 90 red);;*)

let circle radius color = 
  let center = (h/2, w/2) and 
  pow x = x * x in 
  fun (x, y) -> 
  if int_of_float (sqrt (float_of_int (pow (y - snd center) + pow (x - fst center)))) = radius then color 
  else background;;

(*render (circle 50 red);;*)

let move (p: picture) x y = 
  fun (x', y') -> p (x + x', y + y');;

(*render (move (square 90 red) 10 (-50));; *)

let vertical_symmetry (p: picture) = 
  fun (x, y) -> p (-x, y);;

let horizontal_symmetry (p: picture) = 
  fun (x, y) -> p (x, -y);;


(*Exercice 2 *)

let v_lines n = fun (x, y) -> 
  if y mod n = 0 then black else background;;

(*render (v_lines 50);;*)

let v_stripes n : picture = 
  fun (x, y) -> if x mod ((2*n) + 1) < n then black else background;;

(*render (v_stripes 5);;*)

let chessboard color n = 
  fun (x, y) -> if x mod ((2*n) + 1) < n && y mod ((2*n) + 1) < n 
  || ((x+n) mod ((2*n) + 1) < n && (y + n) mod ((2*n) + 1) < n)
  then color else background;;

(*render (chessboard red 30);;*)


let concentric color n = 
  let center = (h/2, w/2) and 
  pow x = x * x in 
  fun (x, y) -> 
  if int_of_float (sqrt (float_of_int (pow (y - snd center) + pow (x - fst center)))) mod (2*n) <= n then color 
  else background;;

(*render (concentric red 50);;*)

let compose_two p1 p2 : picture = 
  fun (x, y) -> if p2 (x, y) = background then p1 (x, y) else p2 (x, y);;

let compose pictures : picture = 
  let rec aux p_list acc = 
  match p_list with
    | [] -> acc
    | h::t -> aux t (compose_two h acc)
  in aux pictures (fun p -> background);;

(*render (compose_two (chessboard yellow 100) (concentric red 64));;*)



let shadow_mickey = 
  let center = (h/2, w/2) in
  let ear = (disk 50 black) and head  = disk 100 black in
  let l_ear = move ear ((fst center) - 180) (-(snd center) + 180)
  and r_ear = move ear ((fst center) - 360) (-(snd center) + 180)
  in
  let placed_head = move head ((fst center) - 270) (-(snd center) + 280)
  in compose [l_ear; r_ear; placed_head]
  ;;

render shadow_mickey;;


let mickey =
  let center = (h/2, w/2) in
  let ear = (disk 50 black) and head  = disk 100 black and skin = disk 90 (blue)
  and eye = disk 10 black and noise = disk 18 black in
  let l_ear = move ear 95 (-100)
  and r_ear = move ear (-95) (-100)
  and l_eye = move eye (30) (-30)
  and r_eye = move eye (-30) (-30)
  in compose [l_eye; r_eye; noise; skin; head ; l_ear; r_ear]
  
;;
render mickey;;




