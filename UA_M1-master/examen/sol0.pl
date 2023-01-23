:- use_module('./pl-man-game/main').
look(DIR, OBJ) :- see(normal, DIR, OBJ).
inventory(OBJ) :- havingObject(appearance(OBJ)).

%% do(get(right)) :- look(right, o), not(look(up, '#')).
%% do(use(right)) :- inventory(o), look(up, '#').
%% do(move(up)) :- not(look(up, '#')), inventory(o).
%% do(move(down)) :- look(up, '#').
%% do(move(none)).

%% COJE COCOS
do(move(right)) :- look(right, '.').
do(move(down)) :- look(down, '.').
do(move(left)) :- look(left, '.').

%% COJE LA PELOTA Y MUEVETE PARA TIRARLA.
do(use(right)) :- look(right, '|'), inventory(o).
do(move(none)) :- inventory(o), look(right, 'E').
do(move(none)) :- inventory(o), look(down-right, 'E').
do(get(right)) :- look(right, o), not(look(up, '\\')), not(inventory(o)).
do(move(up)) :- not(look(up, '#')), inventory(o), not(look(up, '\\')).
do(move(right)) :- look(right, ' '), look(up, '\\'), writeln('derecha 1').
do(move(right)) :- look(up, '#'),not(look(down-right, 'E')), not(look(right, 'E')), not(look(right, '|')), inventory(o), writeln('derecha 2').

%% VUELVE Y RECOJE LA PELOTA
do(move(down)) :- look(left, '#'), not(inventory(o)).
do(move(left)) :- look(up-left,'#'), not(inventory(o)), not(look(left, '0')),  writeln('izq 2').

do(move(none)).


