#lang racket

(define f (lambda(x) (lambda(y) (+ x y))))
(define (g x) ((f x) 3))
(define h (lambda(x) (lambda(y) (y x))))
(define (p f) ((h 2) f))

(define b '(3 14 27))
(define c (cons (car (cdr b))(list 'a 'b 'c)))