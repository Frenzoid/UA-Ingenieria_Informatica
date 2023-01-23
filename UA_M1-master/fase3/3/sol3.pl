:- use_module('./pl-man-game/main').
:- dynamic est/1.
est(cocosizq).
cest(X) :- retractall(est(_)), assert(est(X)).

do(move(up)) :- see(normal, right, '?'), see(normal, up, ' '), est(cocosizq).
do(move(down)) :- see(normal, down, '?'), see(normal, up, ' '), not(see(normal, down-left, '.')), not(see(normal, left, '#')), est(cocosizq), cest(arqueros).

do(move(up)) :- see(normal, up, '.'), est(cocosizq).
do(move(left)) :- see(normal, left, '.'), est(cocosizq).
do(move(down)) :- see(normal, down, '.'), est(cocosizq).
do(move(right)) :- see(normal, right, '.'), est(cocosizq).

do(move(up)) :- see(normal, up, '?'),  not(see(normal, down, '.')), not(see(normal, left, '.')), est(cocosizq), cest(arqueros).
do(move(right)) :- see(normal, right, ' '),  not(see(normal, right, '#')), est(cocosizq).
do(move(up)) :- see(normal, right, '#'),  not(see(normal, up, '#')), not(see(normal, left, '#')), est(cocosizq).
do(move(down)) :- see(normal, right, '?'), est(cocosizq).

%% BUSCA EL TELEPORTADOR
do(move(down)) :- see(normal, down, '?'), est(buscatp), cest(arqueros).
do(move(up)) :- see(normal, up, '?'), est(buscatp), cest(arqueros).
do(move(left)) :- see(normal, left, '?'), est(buscatp), cest(arqueros).
do(move(right)) :- see(normal, right, '?'), est(buscatp), cest(arqueros).

do(move(up)) :- see(normal, up, '?'), est(tparriba), cest(arqueros).
do(move(up)) :- see(normal, left, '#'), est(tparriba).
do(move(up)) :- see(normal, left, '#'), see(normal, down, '#'), est(buscatp), cest(tparriba).
do(move(down)) :- see(normal, right, '#'), see(normal, up, '#'), est(cocosizq), cest(buscatp).
do(move(left)) :- see(normal, left, ' '), est(buscatp).
do(move(down)) :- see(normal, down, ' '), est(buscatp).
do(move(up)) :- see(normal, up, ' '), est(buscatp).

%% ZONA DE ARQUEROS 
do(move(right)) :- see(normal, right, ' '), est(arqueros).
do(move(right)) :- see(normal, right, '.'), est(arqueros).
do(move(left)) :- see(normal, down, '('), est(arqueros), cest(arqueros1).
do(move(down)) :- see(normal, down-left, '<'), est(arqueros1).
do(move(left)) :- see(normal, left, '.'), est(arqueros1).
do(move(none)) :- see(normal, down, '.'), est(arqueros1).
do(move(right)) :- see(normal, down, ')'), est(arqueros1), cest(arqueros2).
do(move(down)) :- see(normal, down-right, '>'), est(arqueros2).
do(move(right)) :- see(normal, right, '.'), est(arqueros2).
do(move(down)) :- see(normal, down, ' '), est(arqueros2), cest(ene).

%% ZONA DE ENEMIGOS
do(move(down)) :- see(normal, left, '#'), see(normal, right, '#'), est(ene).
do(move(left)) :- see(normal, left, ' '), see(normal, up, '#'), est(ene).
do(move(left)) :- see(normal, left, ' '), see(normal, up-left, '#'), est(ene).

do(move(down)) :- see(normal, left, 'E'), not(see(normal, down, '#')), est(ene).
do(move(up)) :- see(normal, left, 'E'), not(see(normal, down, '#')), est(ene).

do(move(left)) :- see(normal,left, '.'), est(ene).
do(move(right)) :- see(normal, right, '.'), est(ene).
do(move(down)) :- see(normal, down, '.'), est(ene).
do(move(up)) :- see(normal, up, '.'), est(ene).


do(move(down)) :- see(normal, down, ' '), see(normal, right, ' '), see(normal, up, '#'), see(normal, left, '#'), est(ene).
do(move(up)) :- see(normal, down-right, ' '), see(normal, down, ' '), see(normal, up, ' '), see(normal, left, ' '), est(ene).
do(move(right)) :- see(normal, right, ' '), not(see(normal, down, '#')), est(ene).
do(move(left)) :- see(normal, left, ' '), see(normal, down, '#'), est(ene).




do(move(none)).