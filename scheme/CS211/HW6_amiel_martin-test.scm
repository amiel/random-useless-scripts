;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  tests for Homework assignment 6 CSCI 311 with Debra Jusak
;;  written by Amiel Martin
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




(require (planet "test.ss" ("schematics" "schemeunit.plt" 2 9))
       (planet "text-ui.ss" ("schematics" "schemeunit.plt" 2 9)))



(load "HW6_amiel_martin.scm")



(define div-test
  (test-suite
   "Tests for div"
   (test-equal? "basic example" (div 7 3) '(2 1))
   (test-equal? "same number" (div 7 7) '(1 0))
   (test-equal? "same number" (div 14 7) '(2 0))
   ))


(define mod-test
  (test-suite
   "Tests for mod"
   (test-equal? "same number: mod 2 2" (mod 2 2) 0)
   (test-equal? "mod 3 2" (mod 3 2) 1)
   (test-equal? "same number: mod 5 5" (mod 5 5) 0)
   (test-equal? "division is 1: mod 7 5" (mod 7 5) 2)
   (test-equal? "division is 2: mod 11 5" (mod 11 5) 1)
   ))

(define gcd-test
  (test-suite
   "Tests for gcd"
   (test-equal? "gcd" (gcd 360 84) 12)
   (test-equal? "gcd" (gcd 1071 1029) 21)
   (test-equal? "gcd" (gcd 6 7) 1)
   ))


(define remove-test
  (test-suite
   "Tests for remove"
   (test-equal? "basic example" (remove 3 '(1 2 3 4 5)) '(1 2 4 5))
   (test-equal? "at end of list" (remove 5 '(1 2 3 4 5)) '(1 2 3 4))
   (test-equal? "at beginning of list" (remove 1 '(1 2 3 4 5)) '(2 3 4 5))
   (test-equal? "multiple occurances" (remove 3 '(3 1 3 2 3 4 5 3)) '(1 2 4 5))
   ))
   
(define uniq-test
  (test-suite
   "Tests for uniq"
   (test-equal? "one duplicate" (uniq '(1 2 3 3 4)) '(1 2 3 4))
   (test-equal? "lots of duplicates, spaced out" (uniq '(1 2 2 3 4 3 1)) '(1 2 3 4))
   (test-equal? "no duplicates" (uniq '(1 2 3 4)) '(1 2 3 4))
   ))



(define included?-test
  (test-suite
   "Tests for included?"
   (test-true "is in list" (included? 2 '(1 2 3 4)))
   (test-false "in not in list" (included? 2 '(1 3 4)))
   ))



(define subset?-test
  (test-suite
   "Tests for subset?"
   (test-true "is in list" (subset? '(2) '(1 2 3 4)))
   (test-true "is in list" (subset? '(2 3) '(1 2 3 4)))
   (test-true "is in list" (subset? '(2 4) '(1 2 3 4)))
   (test-false "in not in list" (subset? '(2) '(1 3 4)))
   ))




(define difference-test
  (test-suite
   "Tests for difference"
   (test-equal? "basic example" (difference '(1 2 3 4) '(1 3)) '(2 4))
   (test-equal? "two equal arguments retuns the empty list" (difference '(1 3 4) '(1 3 4)) '())
   (test-equal? "subtracting the empty list returns L1" (difference '(1 3 4) '()) '(1 3 4))
   (test-equal? "duplicates in L2 go away" (difference '(1 2 3 2 4) '(2 3)) '(1 4))      
   (test-equal? "but duplicates in only L1 don't go away" (difference '(1 2 3 2 4) '(1 3)) '(2 2 4))
   ))


(define set_equal?-test
  (test-suite
   "Tests for set_equal?"
   (test-false "different sizes" (set_equal? '(1 2 3 4) '(1 3)))
   (test-false "same size, not equal" (set_equal? '(1 2 3 4) '(1 2 3 5)))
   (test-true  "same size, equal" (set_equal? '(1 2 3 4) '(1 2 3 4)))
   (test-true  "same size, equal different order" (set_equal? '(1 2 3 4) '(2 1 4 3)))
   (test-true  "different size, duplicates in L1, should be equal" (set_equal? '(1 2 3 3 4) '(2 1 4 3)))
   (test-true  "different size, duplicates in L2, should be equal" (set_equal? '(1 2 3 4) '(2 1 4 4 3)))
   ))

(define set_equal2?-test
  (test-suite
   "Tests for set_equal2?"
   (test-false "different sizes" (set_equal2? '(1 2 3 4) '(1 3)))
   (test-false "same size, not equal" (set_equal2? '(1 2 3 4) '(1 2 3 5)))
   (test-true  "same size, equal" (set_equal2? '(1 2 3 4) '(1 2 3 4)))
   (test-true  "same size, equal different order" (set_equal2? '(1 2 3 4) '(2 1 4 3)))
   (test-true  "different size, duplicates in L1, should be equal" (set_equal2? '(1 2 3 3 4) '(2 1 4 3)))
   (test-true  "different size, duplicates in L2, should be equal" (set_equal2? '(1 2 3 4) '(2 1 4 4 3)))
   ))




(printf "Running tests for div~n")
(test/text-ui div-test)

(printf "Running tests for mod~n")
(test/text-ui mod-test)

(printf "Running tests for gcd~n")
(test/text-ui gcd-test)

(printf "Running tests for remove~n")
(test/text-ui remove-test)

(printf "Running tests for uniq~n")
(test/text-ui uniq-test)

(printf "Running tests for included?~n")
(test/text-ui included?-test)

(printf "Running tests for subset?~n")
(test/text-ui subset?-test)

(printf "Running difference tests~n")
(test/text-ui difference-test)

(printf "Running set_equal? tests~n")
(test/text-ui set_equal?-test)
(printf "Running set_equal2? tests~n")
(test/text-ui set_equal2?-test)
