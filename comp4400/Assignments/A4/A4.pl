% Student Name: Dennis Dao
% Student Number: 110010116 
% Date: Nov 3, 2023

% Problem 1 - Remove Duplicate
% Base case - the list is empty
remove_duplicate([], []).
% A member of the tail - omit from the Seen list
remove_duplicate([H|T], Seen) :- member(H, T), remove_duplicate(T, Seen).
% NOT a member of the tail - include in the Seen list
remove_duplicate([H|T], [H|Seen]) :- \+ member(H, T), remove_duplicate(T, Seen).

% Problem 2 - Course Prerequisites
prerequisite(comp1410, comp1400).
prerequisite(comp1410, comp1000).
prerequisite(comp2120, comp1410).
prerequisite(comp2310, comp1000).
prerequisite(comp2540, comp1410).
prerequisite(comp2140, comp2120).
prerequisite(comp2560, comp1410).
prerequisite(comp2650, comp1410).
prerequisite(comp2660, comp2650).
prerequisite(comp3150, comp2560).
prerequisite(comp3150, comp2540).
prerequisite(comp3220, comp2120).
prerequisite(comp3220, comp2540).
prerequisite(comp3300, comp2540).
prerequisite(comp3300, comp2660).
prerequisite(comp3540, comp2540).
prerequisite(comp3540, comp2310).
prerequisite(comp3670, comp2650).
prerequisite(comp4400, comp2310).
prerequisite(comp4400, comp2540).
prerequisite(comp4400, comp2140).
prerequisite(comp4540, comp3540).

% Helper function from slides to merge a nested prerequisite with the unprocessed prequisites
appd([], L, L).
appd([H|T], L, [H|L2]) :- appd(T, L, L2).

get_all_prerequisites(Course, Prerequisites) :- get_base_prerequisites(Course, X), get_nested_prerequisites(X, All), remove_duplicate(All, Prerequisites).
get_base_prerequisites(Course, Prerequisites) :- findall(One_Answer, prerequisite(Course, One_Answer), Prerequisites).

% Base case - the course has no prereqs
get_nested_prerequisites([], []).
% The course has nested prerequisites
get_nested_prerequisites([H|T], [H|AllPrereqs]) :- get_base_prerequisites(H, PrereqH), appd(PrereqH, T, FullT), get_nested_prerequisites(FullT, AllPrereqs).