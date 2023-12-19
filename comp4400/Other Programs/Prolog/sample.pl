first(X, [X|_]).
like(Y, mary).


len([],0).
len([_|T], X) :- len(T, Y), X is Y + 1.


son(X,Y) :- father(Y,X), male(X). 
daughter(X,Y) :- father(Y,X), female(X). 
grandfather(X,Z) :- father(X,Y), father(Y,Z). 

likes(john, mary). 
likes(dwight, X).  
likes(john, X):-likes(mary, X).
likes(mary, sue).

female(jane). 
female(samantha). 
female(sue). 
male(jake). 
male(ryan). 
male(bill).
father(X,Y):-parent(X,Y), male(X).

parent(bill, dwight). 
parent(dwight, ryan). 
parent(dwight, samantha). 
parent(dwight, sue). 

ancestor(X,Y):-parent(X,Y).
ancestor(X,Z):-parent(X,Y), ancestor(Y,Z).


/* factorial
*/
f(a, b).
f(0, 1).
f(N, F):-N>0, 
         N1 is N-1, f(N1, F1), %recursive call
         F is N*F1. 

even(0).
even(s(s(X))):-even(X).

gparent(X, Y, A):- parent(X, U, A1), parent(U, Y, A2), A is A1+A2. 
parent(a, b, 20).
parent(b, c, 30).

appd([], L, L).
appd([H|T], L, [H|L2]) :- appd(T, L, L2).

mem(X, [X|T]).
mem(X, [H|T]) :- mem(X, T).

rev([],[]).
rev([H|T],L) :- rev(T,Z), append(Z,[H],L).

find_nth([H|T], 1, H).
find_nth([H|T], N, X):-N1 is N-1, find_nth(T,N1,X).

subset([A|X],Y) :- member(A,Y), subset(X,Y).
subset([],Y).

isort([ ],[ ]). 

isort([X|UnSorted], AllSorted) :- 
    isort(UnSorted, Sorted), 
    insert(X, Sorted, AllSorted).
 
insert(X, [ ], [X]). 
insert(X, [Y|L], [X, Y|L]) :- X =< Y. 
insert(X, [Y|L], [Y|IL]) :- X > Y, insert(X, L, IL).

 
change([H,Q,D,N,P]) :- 
    member(H,[0,1,2]),                      /* Half-dollars */ 
    member(Q,[0,1,2,3,4]),                  /* quarters     */ 
    member(D,[0,1,2,3,4,5,6,7,8,9,10]) ,    /* dimes        */ 
    member(N,[0,1,2,3,4,5,6,7,8,9,10,       /* nickels      */ 
               11,12,13,14,15,16,17,18,19,20]),  
    S is 50*H + 25*Q +10*D + 5*N, 
    S =< 100, 
    P is 100-S. 


