#lang racket

; This is the map function
(define (fct F Lst)
    (if(null? Lst)
    Lst
    (cons (F (car Lst)) (fct F (cdr Lst)))
          
    ))

(define f (lambda (x) (lambda (y) (* x y))))
(define (g x) ((f x) 3))
(define h (lambda (x) (lambda (y) (y x))))
(define (p f) ((h 2) f))


;(fct (lambda(x) 1) '(2 3 4))