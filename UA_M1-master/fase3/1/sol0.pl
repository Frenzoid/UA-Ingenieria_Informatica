:- use_module('./pl-man-game/main').
:- dynamic estado/2.

estado(derecha, abajo).

inventory(OBJ) :- havingObject(appearance(OBJ)).
look(DIR, OBJ) :- see(normal, DIR, OBJ).
change(X, Z) :- retractall(estado(_,_)), assert(estado(X,Z)).


%%COJE COCOS
do(get(down)) :- look(down, 8), estado(_, abajo).
do(get(up)) :- look(up, 8), estado(_, abajo).
do(get(left)) :- look(left, 8), estado(_, abajo).
do(get(right)) :- look(right, 8), estado(_, abajo).

do(move(none)) :- look(_, 'E').

do(use(up)) :- look(left, '#'), look(right, '#'), look(up, '*'), change(derecha, arriba).

do(move(none)) :- look(left, '#'), not(look(right, '#')), estado(izquierda, X), change(derecha, X).
do(move(none)) :- look(right, '#'), not(look(left, '#')), estado(derecha, X), change(izquierda, X).

do(move(up)) :- estado(izquierda, arriba), look(up, '.').

do(move(down)) :- look(down, '.').
do(move(left)) :- look(left, '.'), estado(izquierda, _).
do(move(right)) :- look(right, '.'), estado(derecha, _).
do(move(up)) :- look(up, '.').

do(move(up)) :- look(up-left, '#'), look(up-right, '#'), look(up, ' '), estado(_, abajo).
do(move(left)) :- look(left, ' '), estado(izquierda, abajo).
do(move(right)) :- look(right, ' '), estado(derecha, abajo).

do(move(up)) :- not(look(left,'.')), not(look(left,' ')), look(up,'.'), estado(izquierda, abajo).
do(move(up)) :- not(look(left,'.')), not(look(left,' ')), look(up,' '), estado(izquierda, abajo).
do(move(up)) :- not(look(right,'.')), not(look(right,' ')), look(up,' '), estado(derecha, abajo).
do(move(up)) :- not(look(right,'.')), not(look(right,' ')), look(up,' '), estado(derecha, abajo).

do(move(down)) :- not(look(left,'.')), not(look(left,' ')), not(look(up,' ')), not(look(up, '.')), estado(izquierda, abajo).
do(move(down)) :- not(look(right,'.')), not(look(right,' ')), not(look(up,' ')), not(look(up, '.')), estado(derecha, abajo).
do(move(left)) :- not(look(right,'.')), not(look(right,' ')), not(look(up,' ')), not(look(up, '.')), not(look(down,' ')), not(look(down,' ')), not(look(down, '.')), estado(derecha, abajo).


do(move(up)) :- look(left, '#'), look(right, '#'), estado(_, arriba).

do(move(none)).