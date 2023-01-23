:- use_module('./pl-man-game/main').
:- dynamic estado/1.

estado(desconocido).
inventory(OBJ) :- havingObject(appearance(OBJ)).

%% nth(Posicion, Lista, Objeto);
measure(DIR, LONG) :- see(list, DIR, L), length(L, LONG). 
look(DIR, OBJ) :- see(normal, DIR, OBJ).
search(DIR, OBJ, POS) :- see(list, DIR, L), nth0(POS, L, OBJ).
change(X) :- retractall(estado(_)), assert(estado(X)).


do(move(down)) :- search(right, 'F', LD), LD < 6, not(look(down, '#')), not(look(down, 'F')).
do(move(up)) :- search(left, 'F', LL), LL < 6, not(look(up, '#')), not(look(up, 'F')).
do(move(left)) :- search(down,'F', LR), LR < 6, not(look(left, '#')), not(look(left, 'F')).
do(move(right)) :- search(up, 'F', LH), LH < 6, not(look(right, '#')), not(look(right, 'F')).
do(move(up)) :- search(right,'F', LD), LD < 6, not(look(up, '#')), not(look(up, 'F')).
do(move(down)) :- search(left, 'F',LL), LL < 6, not(look(down, '#')), not(look(down, 'F')).
do(move(right)) :- search(down,'F', LR), LR < 6, not(look(right, '#')), not(look(right, 'F')).
do(move(left)) :- search(up,'F', LH), LH < 6, not(look(left, '#')), not(look(left, 'F')).

do(move(none)) :- look(up-left, 'E').
do(move(none)) :- look(up-right, 'E').
do(move(none)) :- look(down-left, 'E').
do(move(none)) :- look(down-right, 'E').

do(move(up)) :- look(down, '#'), look(right, '#'), change(dab).
do(move(up)) :- look(down, '#'), look(left, '#'), change(iab).
do(move(down)) :- look(up, '#'), look(right, '#'), change(dar).
do(move(down)) :- look(up, '#'), look(left, '#'), change(iar).

do(move(left)) :- estado(dar).
do(move(left)) :- estado(dab).
do(move(right)) :- estado(iab).
do(move(right)) :- estado(iar).

do(move(right)) :- search(right, '.',_).
do(move(down)) :- search(down, '.',_).
do(move(up)) :- search(up, '.',_).
do(move(left)) :- search(left, '.',_).
do(move(down)) :-  look(down, ' ').
do(move(right)) :- look(right, ' ').
do(move(left)) :- look(left, ' ').
do(move(up)) :- look(up, ' ').

do(move(none)).
