open OUnit2
open Basics

let test_rev_tup _ =
  assert_equal (1, 2) (rev_tup (2, 1)) ~msg:"rev_tup (1)";
  assert_equal (3, 2) (rev_tup (2, 3)) ~msg:"rev_tup (2)";
  assert_equal (3, 1) (rev_tup (1, 3)) ~msg:"rev_tup (3)";
  assert_equal (1, 1) (rev_tup (1, 1)) ~msg:"rev_tup (4)"

let test_rev_triple _ =
  assert_equal (1, 2, 3) (rev_triple (3, 2, 1)) ~msg:"rev_triple (1)";
  assert_equal (3, 2, 1) (rev_triple (1, 2, 3)) ~msg:"rev_triple (2)";
  assert_equal (3, 1, 1) (rev_triple (1, 1, 3)) ~msg:"rev_triple (3)";
  assert_equal (1, 1, 1) (rev_triple (1, 1, 1)) ~msg:"rev_triple (4)"

let test_is_odd _ =
  assert_equal true (is_odd 1) ~msg:"is_odd (1)";
  assert_equal true (is_odd (9)) ~msg:"is_odd (2)";
  assert_equal false (is_odd 12) ~msg:"is_odd (3)";
  assert_equal false (is_odd 0) ~msg:"is_odd (4)"

let test_is_older _ =
  assert_equal false (is_older (2021, 1, 15) (2020, 1, 16)) ~msg:"is_older (1)";
  assert_equal false (is_older (2022, 1, 15) (2021, 2, 16)) ~msg:"is_older (2)";
  assert_equal false (is_older (2022, 1, 16) (2021, 2, 1)) ~msg:"is_older (3)";
  assert_equal true (is_older (2021, 1, 14) (2021, 1, 15)) ~msg:"is_older (4)"

let test_to_us_format _ =
  assert_equal (1, 15, 2021) (to_us_format (2021, 1, 15)) ~msg:"to_us_format (1)";
  assert_equal (1, 15, 2022) (to_us_format (2022, 1, 15)) ~msg:"to_us_format (2)";
  assert_equal (10, 16, 2022) (to_us_format (2022, 10, 16)) ~msg:"to_us_format (3)";
  assert_equal (12, 6, 2021)  (to_us_format (2021, 12, 6)) ~msg:"to_us_format (4)"

let test_pow _ =
  assert_equal 2 (pow 2 1) ~msg:"pow (1)";
  assert_equal 4 (pow 2 2) ~msg:"pow (2)";
  assert_equal 3 (pow 3 1) ~msg:"pow (3)";
  assert_equal 27 (pow 3 3) ~msg:"pow (4)";
  assert_equal 625 (pow 5 4) ~msg:"pow (5)";
  assert_equal (-27) (pow (-3) 3) ~msg:"pow (6)"

let test_fac _ =
  assert_equal 2 (fac 2) ~msg:"fac (1)";
  assert_equal 24 (fac 4) ~msg:"fac (2)";
  assert_equal 120 (fac 5) ~msg:"fac (3)";
  assert_equal 5040 (fac 7) ~msg:"fac (4)"

let test_get_nth _ =
  assert_equal 26 (get_nth(0, [26; 11; 99])) ~msg:"get_nth (1)";
  assert_equal 11 (get_nth(1, [26; 11; 99])) ~msg:"get_nth (2)";
  assert_equal 99 (get_nth(2, [26; 11; 99])) ~msg:"get_nth (3)"

let test_larger _ =
  assert_equal [1; 2; 3] (larger [1; 2; 3] [5; 6]) ~msg:"larger (1)";
  assert_equal [1; 2; 3] (larger [5; 6] [1; 2; 3]) ~msg:"larger (2)";
  assert_equal [1; 2; 3] (larger [] [1; 2; 3]) ~msg:"larger (3)";
  assert_equal [1; 2; 3] (larger [1; 2; 3] []) ~msg:"larger (4)";
  assert_equal [1] (larger [1] []) ~msg:"larger (5)"


let test_sum _ =
  assert_equal 0 (sum [] []) ~msg:"sum (1)";
  assert_equal 7 (sum [] [3; 4]) ~msg:"sum (2)";
  assert_equal 22 (sum [1; 2; 3; 4] [3; 4; 5]) ~msg:"sum (3)";
  assert_equal 16 (sum [1; 2; 3; 4] [-3; 4; 5]) ~msg:"sum (4)"


let suite =
  "public" >::: [
    "rev_tup" >:: test_rev_tup;
    "rev_triple" >:: test_rev_triple;
    "is_odd" >:: test_is_odd;
    "is_older" >:: test_is_older;
    "to_us_format" >:: test_to_us_format;
    "pow" >:: test_pow;
    "fac" >:: test_fac;
    "get_nth" >:: test_get_nth;
    "larger" >:: test_larger;
    "sum" >:: test_sum
  ]

let _ = run_test_tt_main suite
