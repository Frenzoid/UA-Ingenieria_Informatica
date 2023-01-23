:- use_module('./pl-man-game/main').
:- dynamic estado/1.
:- dynamic disparos/1.
:- dynamic estadoBoss/1.

disparos(0).
estado(desconocido).
inventory(OBJ) :- havingObject(appearance(OBJ)).
estadoBoss(0).

%% nth(Posicion, Lista, Objeto);

measure(DIR, LONG) :- see(list, DIR, L), length(L, LONG). 
look(DIR, OBJ) :- see(normal, DIR, OBJ).
search(DIR, OBJ, POS) :- see(list, DIR, L), nth0(POS, L, OBJ).

change(X) :- retractall(estado(_)), assert(estado(X)).
update(A) :- retractall(estadoBoss(_)), assert(estadoBoss(A)).

%% do(get(down)) :- look(down, l), not(inventory(l)).
%% do(get(up)) :- look(up, l), not(inventory(l)).
%% do(get(left)) :- look(left, l), not(inventory(l)).
%% do(get(right)) :- look(right, l), not(inventory(l)).
%%
%% do(use(left)) :- search(left, 'E', _), inventory(l).
%% do(use(right)) :- search(right, 'E', _), inventory(l).
%% do(use(up)) :- search(up, 'E', _), inventory(l).
%% do(use(down)) :- search(down, 'E', _), inventory(l).

%% DETECTA SI ESTA ABAJO
do(move(none)) :- estado(desconocido), look(down, '#'), look(down-left, '#'), look(down-right, '#'), look(left, '.'), look(right, '.'), change(abajo).  
do(move(none)) :- estado(abajo), look(up, '#'), look(down, ' '), look(up-left, '#'), look(up-right, '#'), change(arriba).

%% MUEVETE PARA ARRIBA
do(move(left)) :- estado(abajo), not(look(left, '#')).
do(move(up)) :- estado(abajo), not(search(up, 'E',_)), not(look(up, '#')).

%% AVOIDEA ENEMIGOS
do(move(up)) :- measure(up, U), measure(down, D), D > U, search(left, 'E', LE), LE < 7.
do(move(down)) :- measure(up, U), measure(down, D), U > D, search(right, 'E', RE), RE < 7.
do(move(up)) :- measure(up, U), measure(down, D), D > U, search(right, 'E', RE), RE < 7.
do(move(down)) :- measure(up, U), measure(down, D), U > D, search(left, 'E', LE), LE < 7.

%% QUEDATE QUIETO OSTIAS
do(move(none)) :- search(down, 'E', _); search(up, 'E', _).

%% RECOLECTA COCOS
do(move(right)) :- search(right, '.', _).
do(move(left)) :- search(left, '.', _).
do(move(up)) :- search(up, '.', _).
do(move(down)) :- search(down, '.', _).

 
do(move(right)) :- look(right, ' '), not(look(right, '#')).
do(move(up)) :- look(up, ' '), not(look(up, '#')).


