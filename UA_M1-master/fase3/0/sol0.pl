:- use_module('./pl-man-game/main').
:- dynamic estado/1.
:- dynamic movimientosCentro/1.

movimientosCentro(0).
estado(desplazar-centro).

inventory(OBJ) :- havingObject(appearance(OBJ)).
look(DIR, OBJ) :- see(normal, DIR, OBJ).
change(X) :- retractall(estado(_)), assert(estado(X)).

%% REGLAS DE LA SALA CENTRAL
do(move(none)) :- look(up, '#'), look(down, '#'), look(left, '#'), look(right, ' '), estado(desplazar-centro), change(det-centro).

do(get(up)) :- estado(desplazar-centro), look(up, '+').
do(get(right)) :- estado(desplazar-centro), look(right, '+').
do(get(left)) :- estado(desplazar-centro), look(left, '+').
do(get(down)) :- estado(desplazar-centro), look(down, '+').

do(move(right)) :- estado(desplazar-centro), see(normal,right,'.').
do(move(up)) :- estado(desplazar-centro), see(normal,up,'.').
do(move(down)) :- estado(desplazar-centro), see(normal,down,'.').
do(move(left)) :- estado(desplazar-centro), see(normal,left,'.').

do(move(left)) :- estado(desplazar-centro), see(normal,left,' ').
do(move(up)) :- estado(desplazar-centro), see(normal,up,' ').
do(move(down)) :- estado(desplazar-centro), see(normal,down,' ').
do(move(right)) :- estado(desplazar-centro), see(normal,right,' ').



%% REGLAS DE DETONACION EN SALA CENTRAL
do(move(none)) :- look(up, '#'), look(down, '#'), look(left, ' '), look(right, '#'), estado(det-centro), change(desplazar-izq).

do(move(right)) :- estado(det-centro), not(inventory('+')).
do(move(right)) :- estado(det-centro), look(up, '#'),  look(down, '#'),  look(left, '#'), look(right, ' '), inventory('+').
do(drop(left)) :- estado(det-centro), inventory('+').



%% REGLAS DE LA SALA IZQ
do(move(down)) :- look(up, '#'), look(down, ' '), look(left, '.'), look(right, ' '), estado(desplazar-izq), change(desplazar-izq-cuidadoso).

do(get(down)) :- estado(desplazar-izq), look(down, '+').
do(get(up)) :- estado(desplazar-izq), look(up, '+').
do(get(right)) :- estado(desplazar-izq), look(right, '+').
do(get(left)) :- estado(desplazar-izq), look(left, '+').

do(move(right)) :- estado(desplazar-izq), look(left, '#').

do(move(left)) :- estado(desplazar-izq), see(normal,left,'.').
do(move(right)) :- estado(desplazar-izq), see(normal,right,'.').
do(move(up)) :- estado(desplazar-izq), see(normal,up,'.').
do(move(down)) :- estado(desplazar-izq), see(normal,down,'.').

do(move(down)) :- estado(desplazar-izq), see(normal,down,' ').
do(move(left)) :- estado(desplazar-izq), see(normal,left,' ').
do(move(up)) :- estado(desplazar-izq), see(normal,up,' ').
do(move(right)) :- estado(desplazar-izq), see(normal,right,' ').

%% REGLAS DE LA SALA IZQ - DESPLAZAMIENTO CUIDADOSO
do(move(left)) :- look(up, '#'), look(down, '#'), look(left, ' '), look(right, '#'), estado(desplazar-izq-cuidadoso), change(det-derecha).

do(move(up)) :- look(up, '.'), not(look(up-left, 'E')), not(look(up-right, 'E')), estado(desplazar-izq-cuidadoso).
do(move(none)) :- look(up, 'E'), estado(desplazar-izq-cuidadoso).
do(move(none)) :- look(up-right, 'E'), estado(desplazar-izq-cuidadoso).
do(move(none)) :- look(up-left, 'E'), estado(desplazar-izq-cuidadoso).
do(move(down)) :- look(up, '#'), estado(desplazar-izq-cuidadoso).
do(move(left)) :- look(up-left, '.'), estado(desplazar-izq-cuidadoso).
do(move(right)) :- look(up-right, '.'), estado(desplazar-izq-cuidadoso).
do(move(right)) :- look(left, ' '), look(right, ' '), look(down, ' '), estado(desplazar-izq-cuidadoso).


%% REGLAS DE LA DETONACION MINA IZQUIERDA
do(move(none)) :- look(right, ' '), look(left, ' '), look(up, ' '), look(down, ' '), look(up-right, ' '), look(down-right, ' '), estado(det-derecha), change(desplazar-derecha-cuidadoso).

do(drop(right)) :- look(up-right, '#'), look(down-right, '#'), estado(det-derecha), inventory('+').
do(move(left)) :- look(right, '+'), estado(det-derecha), not(inventory('+')).


%% REGLAS DE LA DERECHA - DESPLAZAMIENTO CUIDADOSO
do(move(left)) :- look(up, '#'), look(right, '#'), look(up-left, '#'), look(down-right, '#'), estado(desplazar-derecha-cuidadoso), change(detonacion-superior).

do(get(down)) :- estado(desplazar-derecha-cuidadoso), look(down, '+').
do(get(up)) :-  estado(desplazar-derecha-cuidadoso), look(up, '+').
do(get(right)) :-  estado(desplazar-derecha-cuidadoso), look(right, '+').
do(get(left)) :-  estado(desplazar-derecha-cuidadoso), look(left, '+').

do(move(up)) :- look(down, '#'), estado(desplazar-derecha-cuidadoso).
do(move(right)) :- look(right, '.'), estado(desplazar-derecha-cuidadoso).
do(move(down)) :- look(down, '.'), not(look(down-left, 'E')), not(look(down-right, 'E')), estado(desplazar-derecha-cuidadoso).
do(move(none)) :- look(down, 'E'), estado(desplazar-derecha-cuidadoso).
do(move(none)) :- look(down-right, 'E'), estado(desplazar-derecha-cuidadoso).
do(move(none)) :- look(down-left, 'E'), estado(desplazar-derecha-cuidadoso).
do(move(left)) :- look(left, '.'), estado(desplazar-derecha-cuidadoso).

do(move(right)) :- look(down-right, '.'), estado(desplazar-derecha-cuidadoso).
do(move(left)) :- look(down-left, '.'), estado(desplazar-derecha-cuidadoso).

do(move(up)) :- look(up, ' '), not(look(right, '#')),  estado(desplazar-derecha-cuidadoso).
do(move(right)) :- look(up, '#'), not(look(right, '#')),  estado(desplazar-derecha-cuidadoso).

%% MOVIMIENTOS PARA LA DETONACION E INCURSION A LA ZONA SUPERIOR.
do(move(left)) :- look(up, '#'), look(up-left, ' '), look(up-right, '#'), not(inventory('+')), estado(detonacion-superior), change(superior).

do(move(right)) :- not(inventory('+')), look(left, '+'), estado(detonacion-superior).
do(move(left)):- movimientosCentro(N), N < 11, movimientosCentro, estado(detonacion-superior).
do(drop(left)) :- movimientosCentro(N), N > 10, estado(detonacion-superior), inventory('+').


%% MOVIMIENTOS SUPERIOR
do(move(right)) :- look(down, '#'), look(up, '#'), look(left, ' '), estado(superior).
do(move(right)) :- look(up-left, '#'), look(down-left, '#'), look(left, ' '), look(right, ' '), look(up, ' '), estado(superior), change(centro-limpieza).
do(move(none)) :- look(right-up, '<'), estado(superior).
do(move(none)) :- look(right-down, '<'), estado(superior).

do(move(left)) :- look(left, '.'), estado(superior).

do(move(up)) :- look(down, '#'), estado(superior).
do(move(down)) :- look(up, '#'), estado(superior).

do(move(up)) :- look(up, '.'), estado(superior).
do(move(right)) :- look(right, '.'), estado(superior).
do(move(down)) :- look(down, '.'), estado(superior).

do(move(up)) :- look(up, ' '), estado(superior).
do(move(right)) :- look(right, ' '), estado(superior).


%% CENTRO SUPERIOR LIMPIEZA
do(move(left)) :- look(right, '#'), look(up-right, '#'), look(down-right, '#'), estado(centro-limpieza), change(centro-derecha).
do(move(up)) :- look(down, '#'), estado(superior).
do(move(down)) :- look(up, '#'), estado(superior).

do(move(none)) :- look(right-up, '>'), estado(centro-limpieza).
do(move(none)) :- look(right-down, '>'), estado(centro-limpieza).

do(move(up)) :- look(up, '.'), estado(centro-limpieza).
do(move(down)) :- look(down, '.'), estado(centro-limpieza).
do(move(right)) :- look(right, '.'), estado(centro-limpieza).
do(move(right)) :- look(down-right, '.'), estado(centro-limpieza).


%% CENTRO DERECHA
do(move(none)) :- look(right-up, '>'), estado(centro-derecha).
do(move(none)) :- look(right-down, '>'), estado(centro-derecha).

do(move(up)) :- look(down, '#'), estado(centro-derecha).
do(move(down)) :- look(up, '#'), estado(centro-derecha).

do(move(up)) :- look(up, '.'), estado(centro-derecha).
do(move(left)) :- look(left, '.'), estado(centro-derecha).
do(move(down)) :- look(down, '.'), estado(centro-derecha).

do(move(up)) :- look(up, ' '), estado(centro-derecha).
do(move(left)) :- look(left, ' '), estado(centro-derecha).

do(move(none)).
movimientosCentro:- retract(movimientosCentro(M)),N is M+1, assert(movimientosCentro(N)), estado(detonacion-superior).
