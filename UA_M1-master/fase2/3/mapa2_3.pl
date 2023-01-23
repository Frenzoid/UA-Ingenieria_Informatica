%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DIF:	3
%%% PT:	00:30  [STS: 01:30]
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

map_format_version(1.0).
load_behaviour(basicDoorKey).
load_behaviour(mineExplosion).
load_behaviour(entitySequentialMovement).
map([['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '#', '.', '.', '.', '.', '#', '#', '#', '.', '.', '.', '.', '#', '.', '.', '.', '#'],
['#', '.', '.', '#', '#', '#', '.', '.', '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '.', '.', '#'],
['#', '.', '#', '#', '#', '#', '#', '.', '.', '#', '#', '#', '.', '.', '#', '#', ' ', '#', '#', '.', '#'],
['#', '.', '.', '#', '#', '#', ' ', '.', '.', '.', '#', '.', '.', '.', '.', '#', '#', '#', '.', '.', '#'],
['#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]).
map_size(21, 11).
num_dots(111).
pacman_start(1, 1).
initMap:- 
	addSolidObject('#'), 

	% DOORS & KEY
	createGameEntity(OID_D1, '-', object, 19, 5, inactive, norule, 
			[name(puerta_azul_1), solid(true), static(true), use_rule(norule),
			description('Puerta que se abre con la llave azul'), appearance(attribs(normal, black, cyan))]), 
	createGameEntity(OID_D2, '|', object, 16, 8, inactive, norule, 
			[name(puerta_azul_2), solid(true), static(true), use_rule(norule),
			description('Puerta que se abre con la llave azul'), appearance(attribs(normal, black, cyan))]), 
	createGameEntity(OID_K, 'a', object, 16, 5, inactive, norule, 
			[name(llave_azul), solid(false), static(false), use_rule(basicDoorKey),
			description('Llave que abre puertas azules'), appearance(attribs(bold, cyan, default))]), 
	basicDoorKey(init, OID_D1, [ 'pl-man':destroyGameEntity(OID_D1) ], [ OID_K ]),
	basicDoorKey(init, OID_D2, [ 'pl-man':destroyGameEntity(OID_D2) ], [ OID_K ]),

	% MINE
	createGameEntity(OID_M, '+', object, 6, 6, active, mine, 
			[name(mina), solid(false), static(false), use_rule(norule),
			description('Mina que explota nada mas depositarla en el suelo'), appearance(attribs(bold, cyan, default))]), 
	mine(init, OID_M, 1, 1, [ no_destroy(['.']) ]),

	% ENEMIES
	createGameEntity(EID_0, 'E', mortal, 7, 1, active,  entitySequentialMovement, [appearance(attribs(normal, red, default))]), 
	createGameEntity(EID_1, 'E', mortal, 13, 8, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]),
	entitySequentialMovement(init, EID_0, [ d,d,d,d,d,d,d,r,r,r,r,r,r,u,u,u,u,u,u,u,l,l,l,l,l,l ], [ no_repeat_moves ]),
	entitySequentialMovement(init, EID_1, [ u,u,u,u,u,u,u,l,l,l,l,l,l,d,d,d,d,d,d,d,r,r,r,r,r,r ], [ no_repeat_moves ]).

norule(_).
norule(_,_,_,_,_).
