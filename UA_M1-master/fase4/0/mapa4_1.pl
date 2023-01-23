%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DIF:	2
%%% PT:	01:30	[STS: 06:00]
%%%
%%% INDETERMINISMOS DE ESTE MAPA
%%%------------------------------------------------------------
%%% Este mapa cuenta con 3 factores indeterministas que se
%%% describen a continuación:
%%% 1) Aparicion del BOSS:
%%%	El boss es un enemigo gigante formado por muchos enemigos
%%%	pequeños. Aparece en la zona central del mapa (no tocando
%%%	ni la primera ni la última fila), en una columna aleatoria.
%%%	Su movimiento es siempre de izquierda a derecha.
%%% 2) Aparición de las armas:
%%%	En este mapa puede aparecer hasta un máximo de 1 pistola 
%%%	aleatoriamente en uno de sus puntos de renacimiento 
%%%	(respawn points). Los respawns de las armas están en las 
%%%	columnas laterales (la 1 y la 27), pudiendo aparecer en
%%%	cualquier fila (1 a 13)
%%% 3) Posición inicial de Pl-Man
%%%	Pl-Man aparece aleatoriamente en la primera o en la última
%%%	fila del mapa, y en cualquier columna. Concretamente, en
%%%	filas 1 o 13, y en columnas 1 a 27.
%%%
%%% El resto de elementos del mapa son deterministas.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

map_format_version(1.0).
load_behaviour(gunBasic).
load_behaviour(respawnPoint).
load_behaviour(enemyBasicMovement).
map([['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]).
map_size(29, 14).
num_dots(324).
pacman_start(X, Y):- randomFromList(Y, [1, 12]), randomBetween(1, 27, X).
initMap:- 
	addSolidObject('#'),
	
	% BOSS-ENEMY
	randomBetween(0, 16, DX),
	randomFromList(MOV, [left-right, right-left]),
	LB=[p(5,2), p(6,2), p(7,2), 
	p(5,3), p(6,3), p(7,3), 
	p(6,4), 
	p(3,5), p(4,5), p(5,5), p(6,5), p(7,5), p(8,5), p(9,5), 
	p(2,6), p(3,6), p(5,6), p(6,6), p(7,6), p(9,6), p(10,6), 
	p(1,7), p(2,7), p(5,7), p(6,7), p(7,7), p(10,7), p(11,7), 
	p(5,8), p(6,8), p(7,8), 
	p(4,9), p(5,9), p(7,9), p(8,9), 
	p(3,10), p(4,10), p(8,10), p(9,10), 
	p(2,11), p(3,11), p(9,11), p(10,11) ],
	forall(member(p(X,Y), LB), 
	(
		RX is X + DX,
		createGameEntity(EID, 'E', mortal, RX, Y, active, enemyBasicMovement, [appearance(attribs(normal, red, default))]),
		enemyBasicMovement(init, EID, MOV, ['#'])
	)),

	% Weapon Respawn
	createGameEntity(OID_WR1, '', non_interactive, 1, rnd(1,12), active, enemyBasicMovement, 
			[name(respawn_de_arma1), solid(false), static(true), use_rule(norule),
			description('Aqui aparecen armas'), appearance(attribs(normal, default, default))]), 
	createGameEntity(OID_WR2, '', non_interactive, 27, rnd(1,12), active, enemyBasicMovement, 
			[name(respawn_de_arma2), solid(false), static(true), use_rule(norule),
			description('Aqui aparecen armas'), appearance(attribs(normal, default, default))]), 
	enemyBasicMovement(init, OID_WR1, up-down, ['#']),
	enemyBasicMovement(init, OID_WR2, down-up, ['#']),
	respawnPoint(init, [OID_WR1, OID_WR2], 1, 
		[ app('l'), name(pistola), use_rule(gunBasic), description('Pistola con 6 balas'), 
		  active(inactive), type(object), appearance(attribs(bold, cyan, default)) ],
		[ OID, 'pl-man':gunBasic(init, OID, 6, [ 'E', 'l' ], destroy) ], [ probRespawn(250) ] ).

norule(_).
norule(_,_,_,_,_).
