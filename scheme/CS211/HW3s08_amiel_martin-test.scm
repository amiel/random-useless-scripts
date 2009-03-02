;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  tests for Homework assignment 3 CSCI 311 with Debra Jusak
;;  written by Amiel Martin
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




(require (planet "test.ss" ("schematics" "schemeunit.plt" 2 9))
       (planet "text-ui.ss" ("schematics" "schemeunit.plt" 2 9)))



(load "HW3s08_amiel_martin.scm")


(define exclusive-or-test
 (test-suite
  "Tests for exclusive-or"
  (test-equal? "true  true " (exclusive-or #t #t) #f)
  (test-equal? "true  false" (exclusive-or #t #f) #t)
  (test-equal? "false true " (exclusive-or #f #t) #t)
  (test-equal? "false false" (exclusive-or #f #f) #f)

  )) 

(define find-after-test
 (test-suite
  "Tests for find-after"
  (test-equal? "includes element" (find-after 3 '(1 2 3 4 5)) '(4 5))
  (test-equal? "without element" (find-after 3 '(1 2 4 5)) () )
  (test-equal? "element at the end of the list" (find-after 3 '(1 2 3)) '())
  (test-equal? "elements are lists" (find-after '(1 2) '((1 3) (2 1) (1 2 3) (1 2) (2 1 3) (3 1))) '((2 1 3) (3 1)))
  )) 


(define insert-test
  (test-suite
   "Tests for insert"
   (test-equal? "basic example" (insert 2 '(1 2 3 4)) '(1 2 2 3 4))
   (test-equal? "not in list" (insert 2 '(1 3 4)) '(1 3 4))
   (test-equal? "in list twice" (insert 2 '(1 2 3 2 4)) '(1 2 2 3 2 4))
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



(define set-union-test
  (test-suite
   "Tests for set-union"
   (test-equal? "basic example" (set-union '(1 2 3) '(2 3 4)) '(1 2 3 4))
   (test-equal? "with already duplicates" (set-union '(1 1 2 2 3 3) '(2 2 3 3 4 4)) '(1 2 3 4))
   (test-equal? "with none in common" (set-union '(1 2 3) '(4 5)) '(1 2 3 4 5))
   (test-equal? "A union A = A" (set-union '(1 2 3 4) '(4 3 2 1)) '(1 2 3 4))
   (test-equal? "example from class" (set-union '(a b c) '(b c d)) '(a b c d))
   ))

(define included?-test
  (test-suite
   "Tests for included?"
   (test-true "is in list" (included? 2 '(1 2 3 4)))
   (test-false "in not in list" (included? 2 '(1 3 4)))
   ))


(define set-intersection-test
  (test-suite
   "Tests for set-intersection"
   (test-equal? "basic example" (set-intersection '(1 2 3) '(2 3 4)) '(2 3))
   (test-equal? "with already duplicates" (uniq (set-intersection '(1 1 2 2 3 3) '(2 2 3 3 4 4))) '(2 3))
   (test-equal? "with none in common" (set-intersection '(1 2 3) '(4 5)) '())
   (test-equal? "A intersection A = empty" (set-intersection '(1 2 3 4) '(4 3 2 1)) '(1 2 3 4))
   ))

(define set-difference-test
  (test-suite
   "Tests for set-difference"
   (test-equal? "basic example" (set-difference '(1 2 3 4) '(1 3)) '(2 4))
   (test-equal? "two equal arguments retuns the empty list" (set-difference '(1 3 4) '(1 3 4)) '())
   (test-equal? "subtracting the empty list returns L1" (set-difference '(1 3 4) '()) '(1 3 4))
   (test-equal? "duplicates in L2 go away" (set-difference '(1 2 3 2 4) '(2 3)) '(1 4))      
   (test-equal? "but duplicates in only L1 don't go away" (set-difference '(1 2 3 2 4) '(1 3)) '(2 2 4))
   ))

(define symmetric-difference-test
  (test-suite
   "Tests for symmetric-difference"
   (test-equal? "basic example" (symmetric-difference '(1 2 3) '(2 3 4)) '(1 4))
   (test-equal? "both same" (symmetric-difference '(1 2 3) '(1 2 3)) '())
   (test-equal? "no common elems" (symmetric-difference '(1 2 3) '(4 5 6)) '(1 2 3 4 5 6))
   (test-equal? "another basic example" (symmetric-difference '(1 2 3 4) '(3 4 5 6)) '(1 2 5 6))
   ))



(printf "Running tests for exclusive-or~n")
(test/text-ui exclusive-or-test)

(printf "Running tests for find-after~n")
(test/text-ui find-after-test)

(printf "Running tests for insert~n")
(test/text-ui insert-test)

(printf "Running tests for remove~n")
(test/text-ui remove-test)

(printf "Running tests for uniq~n")
(test/text-ui uniq-test)

(printf "Running tests for set-union~n")
(test/text-ui set-union-test)

(printf "Running tests for included?~n")
(test/text-ui included?-test)

(printf "Running tests for set-intersection~n")
(test/text-ui set-intersection-test)

(printf "Running set-difference tests~n")
(test/text-ui set-difference-test)

(printf "Running tests for symmetric-difference~n")
(test/text-ui symmetric-difference-test)