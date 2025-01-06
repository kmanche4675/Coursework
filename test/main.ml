open OUnit2
open Interp
open Ast
open Main

(** [make_i n i s] makes an OUnit test named [n] that expects
    [s] to evaluate to [Int i]. *)
let make_i n i s =
  n >:: (fun _ -> assert_equal (Int i) (interp s))

(** [make_b n b s] makes an OUnit test named [n] that expects
    [s] to evaluate to [Bool b]. *)
let make_b n b s =
  n >:: (fun _ -> assert_equal (Bool b) (interp s))

(** [make_t n s] makes an OUnit test named [n] that expects
    [s] to fail type checking with error string [s']. *)
let make_t n s' s =
  n >:: (fun _ -> assert_raises (Failure s') (fun () -> interp s))

let string_of_val (e : expr) : string =
  match e with
  | Int i -> string_of_int i
  | Bool b -> string_of_bool b
  | _ -> failwith "precondition violated"

let is_value : expr -> bool = function 
  | Int _ | Bool _ -> true
  | Var _ | Let _ | Binop _ | If _ -> false

let rec subst e v x = match e with
  | Var y -> if x = y then v else e
  | Bool _ | Int _ -> e
  | Binop (bop, e1, e2) -> Binop (bop, subst e1 v x, subst e2 v x)
  | Let (y, e1, e2) ->
      let e1' = subst e1 v x in
      if x = y
      then Let (y, e1', e2)
      else Let (y, e1', subst e2 v x)
  | If (e1, e2, e3) -> If (subst e1 v x, subst e2 v x, subst e3 v x)

let rec step : expr -> expr = function
  | Int _ | Bool _ -> failwith "Does not step"
  | Var _ -> failwith unbound_var_err
  | Let (x, e1, e2) when is_value e1 -> subst e2 e1 x
  | Let (x, e1, e2) -> Let (x, step e1, e2)
  | If (Bool true, e2, _) -> e2
  | If (Bool false, _, e3) -> e3
  | If (Int _, _, _) -> failwith if_guard_err
  | If (e1, e2, e3) -> If (step e1, e2, e3)
  | Binop (bop, e1, e2) when is_value e1 && is_value e2 -> step_bop bop e1 e2
  | Binop (bop, e1, e2) when is_value e1 -> Binop (bop, e1, step e2)
  | Binop (bop, e1, e2) -> Binop (bop, step e1, e2)

and step_bop bop e1 e2 = match bop, e1, e2 with
  | Add, Int a, Int b -> Int (a + b)
  | Sub, Int a, Int b -> Int (a - b)
  | Mul, Int a, Int b -> Int (a * b)
  | Div, Int a, Int b -> Int (a / b)
  | Leq, Int a, Int b -> Bool (a <= b)
  | _ -> failwith bop_err

let tests = [
  make_i "int" 22 "22";
  make_i "add" 22 "11+11";
  make_i "adds" 22 "(10+1)+(5+6)";
  make_i "let" 22 "let x=22 in x";
  make_i "lets" 22 "let x = 0 in let x = 22 in x";
  make_i "mul1" 22 "2*11";
  make_i "mul2" 22 "2+2*10";
  make_i "mul3" 14 "2*2+10";
  make_i "mul4" 40 "2*2*10";
  make_i "if1" 22 "if true then 22 else 0";
  make_b "true" true "true";
  make_b "leq" true "1<=1";
  make_i "if2" 22 "if 1+2 <= 3+4 then 22 else 0";
  make_i "if3" 22 "if 1+2 <= 3*4 then let x = 22 in x else 0";
  make_i "letif" 22 "let x = 1+2 <= 3*4 in if x then 22 else 0";
  make_t "invalid plus" bop_err "1 + true";
  make_t "invalid mult" bop_err "1 * false";
  make_t "invalid leq" bop_err "true <= 1";
  make_t "invalid guard" if_guard_err "if 1 then 2 else 3";
  make_t "unbound" unbound_var_err "x";
]

let _ = run_test_tt_main ("suite" >::: tests)
