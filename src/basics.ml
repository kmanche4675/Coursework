let abs x =
  if x >= 0 then x
  else (-x)

(***********************************)
(* Part 1: Non-Recursive Functions *)
(***********************************)

let rev_tup (tup: 'a * 'b) = (snd tup, fst tup);;

let rev_triple (tup : 'a * 'b * 'c) =  
  let (a, b, c) = tup in
  (c, b, a);;

let is_odd (x : int) =
if (x mod 2 ) = 0 then false else true;;

let is_older (date1: int * int * int) (date2: int * int * int) = 
   let ( year1, month1,day1) = date1 in 
   let (year2, month2,day2 ) = date2 in
   if year1 < year2 then true
   else if year1 > year2 then false
   else if month1 < month2 then true
   else if month1 > month2 then false 
   else day1 < day2;;
   
let to_us_format (date1: int * int * int) = 
   let (year, month, day) = date1 in
   (month, day, year);;

(*******************************)
(* Part 2: Recursive Functions *)
(*******************************)

let rec pow x p =
  if p = 0  then 1
  else x * pow x (p - 1) ;;

let rec fac (x:int)=
  if x = 0 then 1
  else x * fac (x - 1);;

(*****************)
(* Part 3: Lists *)
(*****************)

let rec get_nth ((idx:int), (lst: 'a list)) =
   match lst with
   | [] -> failwith "Index out of bounds"
   | hd:: tl -> if idx = 0 then hd else get_nth (idx - 1, tl);;
let larger lst1 lst2  =  
    match List.length lst1, List.length lst2 with
    | len1, len2 when len1 > len2 -> lst1
    | len1, len2 when len2 > len1 -> lst2
    | _ -> [];;

let rec sum_list lst = 
  match lst with
  |  [] -> 0
  | hd :: tl -> hd + sum_list tl;;

let sum lst1 lst2 = 
  sum_list lst1 + sum_list lst2;;

