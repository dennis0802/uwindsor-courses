#lang racket

(define (reduce F E0 L)
  (if (null? L)
      E0
      (F (car L)
         (reduce F E0 (cdr L)))
      ))

(define (compose f g)
  (lambda(x)
    (f(g x))))


(define (f x y) 
	(let ((a (+ 1 (* x y)))
	       (b (- 1 y)))
	    (+ (* x a a) (* y b) (* a b))))


(define (member? x lst)
	(cond 
		((null? lst) #f)
		((equal? x (car lst)) #t)
		(else (member? x (cdr lst)))))

(define (factorial n)
        (if (= n 1)
	    1
	    (* n (factorial (- n 1)))))

(define (nth lst n)	; assumes lst is non-empty and n >= 0
	(if (= n 0)
	    (car lst)
	    (nth (cdr lst) (- n 1))))

(define (reverse lst)
	(if (null? lst)
	    lst
	    (append (reverse (cdr lst)) (list (car lst)))))


(define (factorial-interactive)
	(display "Enter an integer: ")
	(let ((n (read)) (x 1))
	   (display "The factorial of ")
	   (display n)
	   (display " is ")
	   (display (factorial n))
	   (newline)))

(define (insert x l)
  (if (null? l)
      (list x)
      (if (<= x (car l))
          (cons x l)
          (cons (car l) (insert x (cdr l))))))

(define (isort l)
  (if (null? l)
      '()
      (insert (car l) (isort (cdr l)))))
