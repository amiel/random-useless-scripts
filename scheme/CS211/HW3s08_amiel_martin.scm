;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  exclusive-or -- expects two arguments
;;  returns false if both arguments evaluate to the same boolean value
;;  returns true otherwise
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(define exclusive-or
  (lambda (a b)
    (and (or a b) (not (and a b)) ) ))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 
;;  find-after, takes two arguments, an atom and a list
;;  if the atom is an element within the list, then find-after
;;  returns a list containing every element after the first
;;  appearance of atom
;;  if the atom is not in the list, the empty list is returned
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define find-after
  (lambda (a L)
    (cond ((null? L) () )
          ((equal? a (car L)) (cdr L))    ;; using equal? because it can handle lists
          (else (find-after a (cdr L))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  insert
;;  inserts the first argument a into the list L, after the first
;;  appearance of a in L
;;  returns L if a is not in L
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define insert
  (lambda (a L)
    (cond ((null? L) () )
          ((equal? a (car L)) (cons a L) )
          (else (cons (car L) (insert a (cdr L)))) )))



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
;;  uniq -- this function was not required by the homework.
;;  it removes any duplicates in a list 
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
;;  set-union
;;  returns the set containing all elements present in either L1 or L2
;;  as a side effect it also removes all duplicates
;;  example:
;;    (set-union '(1 2 3 4) '(3 4 5 6)) => (1 2 3 4 5 6)
;;
;;  NOTE: this may not be as effecient as the algorithm used in
;;        set-intersection, but this is nice and expressive
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(define set-union
  (lambda (L1 L2)
    (uniq (append L1 L2)) ))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  included? -- this function was not required by the homework
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
;;  set-difference -- this function was not required by the homework
;;  return a list containing all the elements in L1 but not in L2
;;  example:
;;    (set-difference '(1 2 3 4) '(2 4)) => (1 3)
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define set-difference
  (lambda (L1 L2)
    (cond ((null? L1) '())
          ((included? (car L1) L2) (set-difference (cdr L1) L2))
          (else (cons (car L1) (set-difference (cdr L1) L2))) )))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  set-intersection -- this function was not required by the homework
;;  return a list containing each element that is a member of both
;;  L1 AND L2
;;  expects L1 to already be a set
;;  example:
;;    (set-intersection '(1 2 3 4) '(3 4 5 6)) => (3 4)
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define set-intersection
  (lambda (L1 L2)
    (cond ((null? L1) '())
          ((included? (car L1) L2) (cons (car L1) (set-intersection (cdr L1) L2)))
          (else (set-intersection (cdr L1) L2)) )))



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;;  symmetric-difference
;;  this function returns the symetric difference of two sets;
;;  a list including any item that is in either L1 or L2 but not both
;;  example:
;;    (symmetric-difference '(1 2 3 4) '(3 4 5 6)) => (1 2 5 6)
;;
;;  NOTE: this is probably not the most effecient way to write this
;;        function, however, it is very nice this way
;;        it also could have been written in terms of exclusive-or
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define symmetric-difference
  (lambda (L1 L2)
    (set-difference (set-union L1 L2) (set-intersection L1 L2) ) ))

