%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DIF:	3
%%% PT:	__:__	[STS: __:__]
%%%
%%% INDETERMINISMOS DE ESTE MAPA
%%%------------------------------------------------------------
%%% En este mapa sólo hay 1 objeto indeterminista, y es el
%%% teletranportador. En la sala de la izquierda, que tiene
%%% forma de reloj de arena, puede aparecer aleatoriamente en 
%%% cualquiera de sus 4 esquinas. Concretamente, las posiciones
%%% en que puede aparecer son: [1,1], [13,1], [1,7], [13,7]
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

map_format_version(1.0).
load_behaviour(automaticArcher).
load_behaviour(enemyBasicMovement).
load_behaviour(basicTeletransport).
map([['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', '.', '.', '.', '.', '#', '#', '#', '#', '#', '.', '.', '.', '.', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', '#'],
['#', '.', '.', '.', '.', '.', '#', '#', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', '#'],
['#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', ' ', '.', '.', '.', '.', '.', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#'],
['#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'],
['#', '.', '.', '.', '.', '.', '#', '#', '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '#', '#', '#', '#', '#', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]).
map_size(28, 9).
num_dots(120).
pacman_start(7, 4).
initMap:- 
	msgWindowWriteln('El teletransporte puede aparecer en 4 posiciones aleatorias'),
	addSolidObject('#'), 
	% Teletransporte aleatorio 4 esquinas: U-L (1,1); U-R (13,1); D-L (1,7); D-R (13,7)
	createGameEntity(OID_TT, '?', object, rnd([1,13]), rnd([1,7]), active, basicTeletransport, 
			[name('Teletransporte'), solid(false), static(true), use_rule(norule),
			description('Cabina que teletransporta a Pacman'), appearance(attribs(bold, black, white))]), 
	entityLocation(OID_TT, X, Y, _),
	basicTeletransport(init, OID_TT, from(X, Y), to(15, 1), ['@'], []),

	% Arqueros automáticos
	createGameEntity(OID_AR1, '(', object, 26, 2, active, automaticArcher, 
			[name('Arquero1'), solid(false), static(true), use_rule(norule),
			description('Dispara flechas automáticamente'), appearance(attribs(bold, yellow, default))]), 
	createGameEntity(OID_AR2, ')', object, 15, 3, active, automaticArcher, 
			[name('Arquero2'), solid(false), static(true), use_rule(norule),
			description('Dispara flechas automáticamente'), appearance(attribs(bold, yellow, default))]), 
	automaticArcher(init, OID_AR1, ['@'], left , 5, [ continuous, bullet_appearance('<', bold, red, default) ]),
	automaticArcher(init, OID_AR2, ['@'], right, 5, [ continuous, bullet_appearance('>', bold, red, default) ]),
	% Fantasmas
	createGameEntity(EID_0, 'E', mortal, 15, 6, active, enemyBasicMovement, [appearance(attribs(bold, red, default))]), 
	createGameEntity(EID_1, 'E', mortal, 26, 7, active, enemyBasicMovement, [appearance(attribs(bold, red, default))]),
	enemyBasicMovement(init, EID_0, right-left, ['#']),
	enemyBasicMovement(init, EID_1, left-right, ['#']).

norule(_).
norule(_,_,_,_,_).
