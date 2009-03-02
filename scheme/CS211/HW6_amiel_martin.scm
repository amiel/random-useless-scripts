;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  Homework #6 CS211 spring '08
;;  Amiel Martin
;;
;;  includes the following functions
;;  - div -- divide numbers
;;  - mod -- modulo
;;  - gcd -- greatest common divisor
;;  - remove -- remove an item from a list
;;  - uniq -- removes duplicates from a list
;;  - included? -- member of
;;  - subset?
;;  - difference -- set difference
;;  - set_equal? -- set equality, igores duplicates
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  div
;;  divide x by y and return the quotiont and the remainder
;;  (div x y) returns (quotient_of(x/y) remainder_of(x/y))
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define div
  (lambda (dividend divisor)
    (let d ((a dividend) (q 0))
      (if (< a divisor)
          (list q a)
          (d (- a divisor) (+ q 1)) ) )))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  mod
;;  returns the remainder from dividing a by b
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(define mod
  (lambda (a b)
    (car (cdr (div a b))) ))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  gcd -- greatest common divisor
;;  Euclids algorithm
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(define gcd
  (lambda (a b)
    (if (= b 0)
        a
        (gcd b (mod a b)) ) ))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  remove
;;  returns a list with any elements in L that are not a
;;  example:
;;    (remove 2 '(1 2 3 4)) => (1 3 4)
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define remove
  (lambda (a L)
    (cond ((null? L) () )
          ((equal? a (car L)) (remove a (cdr L)) )
          (else (cons (car L) (remove a (cdr L)))) )))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  uniq
;;  removes any duplicates in a list 
;;  Example:
;;    (uniq '(1 2 2 3 4 3)) => (1 2 3 4)
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(define uniq
  (lambda (L)
    (cond ((null? L) () )
          (else (cons (car L) (uniq (remove (car L) L)))) )))




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  included?
;;  expects an atom and a list
;;  returns #t if the atom is a member of the list, returns #f otherwise
;;  examples:
;;    (included? 2 '(1 2 3)) => #t
;;    (included? 2 '(1 3 4)) => #f
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define included?
  (lambda (a L)
    (cond ( (null? L) #f )
          ( (equal? a (car L)) #t )
          (else (included? a (cdr L))) ) ))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  subset?
;;  returns true if every member of L1 is also a member of L2
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define subset?
  (lambda (L1 L2)
    (cond ((null? L1) #t )
          ((included? (car L1) L2) (subset? (cdr L1) L2))
          (else #f) )))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  difference
;;  return a list containing all the elements in L1 but not in L2
;;  example:
;;    (difference '(1 2 3 4) '(2 4)) => (1 3)
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define difference
  (lambda (L1 L2)
    (cond ((null? L1) '())
          ((included? (car L1) L2) (difference (cdr L1) L2))
          (else (cons (car L1) (difference (cdr L1) L2))) )))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  set_equal?
;;  returns true if L1 and L2 contain all the same elements
;;  set_equal2? another version without using subset?
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(define set_equal?
  (lambda (L1 L2)
    (and (subset? L1 L2) (subset? L2 L1)) ))


(define set_equal2?
  (lambda (L1 L2)
    (let se? ((a (uniq L1)) (b L2)) ; remove duplicates from L1. L2 gets duplicates removed from call to (remove
      (cond ((null? a) (null? b))
            ((included? (car a) b) (se? (cdr a) (remove (car a) b)) )
            (else #f) ))))
        
