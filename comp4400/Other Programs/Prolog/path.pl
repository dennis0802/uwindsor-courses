edge(a,b).
edge(b,c).
edge(c,d).
edge(d,e).
edge(b,e).
edge(d,f).
path(X,Y):-edge(X,Z), path(Z,Y).
path(X,X).

