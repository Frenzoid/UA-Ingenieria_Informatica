%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DIF:	3
%%% PT:	__:__	[STS: __:__]
%%%
%%% INDETERMINISMOS DE ESTE MAPA
%%%------------------------------------------------------------
%%% En este mapa los únicos objetos que pueden cambiar de po-
%%% sición son las minas que aparecen. Hay 3 minas, 1 en cada
%%% una de las salas inferiores respectivamente. Cada una de
%%% las minas puede aparecer en cualquier posición dentro de
%%% su sala. Concretamente, las minas pueden aparecer en las
%%% siguientes posiciones:
%%% MINA1: columnas  2- 7 filas 5-7
%%% MINA2: columnas 11-17 filas 5-7
%%% MINA3: columnas 21-27 filas 5-7
%%%
%%% El resto de elementos en este mapa son deterministas.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

map_format_version(1.0).
load_behaviour(mineExplosion).
load_behaviour(automaticArcher).
load_behaviour(entitySequentialMovement).
map([['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', ' ', '.', '.', '.', '.', '.', '.', ' ', '#', ' ', '.', '.', '.', ' ', '.', '.', '.', ' ', '#', ' ', '.', '.', '.', '.', '.', '.', ' ', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', ' ', '.', '.', '.', '.', '.', '.', ' ', '#', ' ', '.', '.', '.', '.', '.', '.', '.', ' ', '#', ' ', '.', '.', '.', '.', '.', '.', ' ', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', ' ', '.', '.', '.', '.', '.', '.', ' ', '#', ' ', '.', '.', '.', '.', '.', '.', '.', ' ', '#', ' ', '.', '.', '.', '.', '.', '.', ' ', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', ' ', '.', '.', '.', '.', '.', '.', ' ', '#', ' ', '.', '.', '.', '.', '.', '.', '.', ' ', '#', ' ', '.', '.', '.', '.', '.', '.', ' ', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]).
map_size(29, 9).
num_dots(127).
pacman_start(18, 7).
initMap:- 
	addSolidObject('#'), 

	% Arithmetic Door
	createGameEntity(OID_M1, '+', object, rnd(2,7), rnd(5,7), active, mine, 
			[name(mina_1), solid(false), static(false), use_rule(norule),
			description('Mina que explota 1 ciclo despues de ser depositada.'), appearance(attribs(bold, cyan, default))]), 
	createGameEntity(OID_M2, '+', object, rnd(11,17), rnd(5,7), active, mine, 
			[name(mina_2), solid(false), static(false), use_rule(norule),
			description('Mina que explota 1 ciclo despues de ser depositada.'), appearance(attribs(bold, cyan, default))]), 
	createGameEntity(OID_M3, '+', object, rnd(21,27), rnd(5,7), active, mine, 
			[name(mina_3), solid(false), static(false), use_rule(norule),
			description('Mina que explota 1 ciclo despues de ser depositada.'), appearance(attribs(bold, cyan, default))]), 
   mine(init, OID_M1, 1, 1, [ no_destroy(['.']) ]),
   mine(init, OID_M2, 1, 1, [ no_destroy(['.']) ]),
   mine(init, OID_M3, 1, 1, [ no_destroy(['.']) ]),

	% Automatic Archers
	createGameEntity(OID_AR1, '(', object, 8, 1, active, automaticArcher, 
			[name(arquero), solid(false), static(true), use_rule(norule),
			description('Arquero automatico del rey'), appearance(attribs(bold, yellow, default))]), 
	createGameEntity(OID_AR2, ')', object, 20, 1, active, automaticArcher, 
			[name(arquero), solid(false), static(true), use_rule(norule),
			description('Arquero automatico del rey'), appearance(attribs(bold, yellow, default))]), 
	createGameEntity(OID_AR3, '(', object, 8, 3, active, automaticArcher, 
			[name(arquero), solid(false), static(true), use_rule(norule),
			description('Arquero automatico del rey'), appearance(attribs(bold, yellow, default))]), 
	createGameEntity(OID_AR4, ')', object, 20, 3, active, automaticArcher, 
			[name(arquero), solid(false), static(true), use_rule(norule),
			description('Arquero automatico del rey'), appearance(attribs(bold, yellow, default))]), 
	automaticArcher(init, OID_AR1, ['@'], left, 5, [ continuous, bullet_appearance('<', bold, red, default) ]),
	automaticArcher(init, OID_AR3, ['@'], left, 6, [ continuous, bullet_appearance('<', bold, red, default) ]),
	automaticArcher(init, OID_AR2, ['@'], right, 5, [ continuous, bullet_appearance('>', bold, red, default) ]),
	automaticArcher(init, OID_AR4, ['@'], right, 6, [ continuous, bullet_appearance('>', bold, red, default) ]),

	% Entities
	createGameEntity(EID_0, 'E', mortal, 1, 5, active,  entitySequentialMovement, [appearance(attribs(normal, red, default))]), 
%	createGameEntity(EID_1, 'E', mortal, 10, 7, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]), 
	createGameEntity(EID_2, 'E', mortal, 27, 7, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]),
	entitySequentialMovement(init, EID_0, [ r,r,r,r,r,r,n,l,l,l,l,l,l,n ], [ no_repeat_moves ]),
%	entitySequentialMovement(init, EID_1, [ u,u,r,r,r,r,r,r,r,r,d,d,l,l,l,l,l,l,l,l ], [ no_repeat_moves ]),
	entitySequentialMovement(init, EID_2, [ l,l,l,l,l,l,n,r,r,r,r,r,r,n ], [ no_repeat_moves ]).

norule(_).
norule(_,_,_,_,_).
