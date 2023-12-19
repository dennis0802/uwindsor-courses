; Developer: Dennis Dao
; Date: October 2, 2023
; Student Number: 110010116

#lang racket

; Function to retrieve operator, always 2nd item of an expression
(define (operator x) (eval(cadr x)))
; Function to get expr without first 3 characters (ex. ... + 1 + 2 + 3)
(define (exprTail x) (cdr(cdr(cdr x))))

; NOTE: THIS IS A LEFT ASSOCIATIVE CALCULATOR! (ex. [x+y]+z => res1 + z)
(define calculator
  (lambda(x)
    (cond
      ; Base case has exactly 3 characters, recursive makes an expression with leftmost result and tail
      ((null? x) 0)
      ((and (number? x) (not (list? x))) x)
      ((= (length x) 1) (car x))
      (else (calculator(cons ((operator x) (car x) (caddr x)) (exprTail x))))
 )))