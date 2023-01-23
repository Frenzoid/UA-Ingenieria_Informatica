%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DIF:	2
%%% PT:	00:15 [STS: 00:45]
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

map_format_version(1.0).
load_behaviour(basicDoorKey).
load_behaviour(entitySequentialMovement).
map([['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', ' ', '.', '#'],
['#', '.', ' ', '#', '.', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '.', '.', '#'],
['#', '.', ' ', '#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', ' ', '.', '#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', ' ', '#', '.', '.', '#', '.', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '.', '.', '#'],
['#', ' ', '.', '#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'],
['#', '.', ' ', '#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', '#', '.', '.', '.', '#'],
['#', '.', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]).
map_size(22, 12).
num_dots(140).
pacman_start(16, 7).
initMap:- 
	addSolidObject('#'), 
	createGameEntity(OID_K, 'a', object, 19, 1, inactive, norule, 
			[name(llave_azul), solid(false), static(false), use_rule(basicDoorKey),
			description('Llave que abre la puerta azul'), appearance(attribs(bold, cyan, default))]), 
	createGameEntity(OID_D, '|', object, 17, 10, inactive, norule, 
			[name(puerta_azul), solid(true), static(true), use_rule(norule),
			description('Puerta que se abre con la llave azul'), appearance(attribs(normal, black, cyan))]), 
	basicDoorKey(init, OID_D, [ 'pl-man':destroyGameEntity(OID_D) ], [ OID_K ]),
	createGameEntity(EID_0, 'E', mortal, 20, 3, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]), 
	createGameEntity(EID_1, 'E', mortal, 6, 9, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]), 
	createGameEntity(EID_2, 'E', mortal, 19, 10, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]),
	entitySequentialMovement(init, EID_0, [ l,l,l,l,l,l,l,l,l,l,l,l,l,d,r,r,r,r,r,r,r,r,r,r,r,r,r,u ], [ no_repeat_moves ]),
	entitySequentialMovement(init, EID_1, [ l,l,l,l,u,u,u,u,u,u,u,u,l,d,d,d,d,d,d,d,d,d,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,u,l,l,l,l,l,l,l,l,l,l ], [ no_repeat_moves ]),
	entitySequentialMovement(init, EID_2, [ u,u,u,u,u,u,u,u,u,n,d,d,d,d,d,d,d,d,d,n ], [ no_repeat_moves ]).

norule(_).
norule(_,_,_,_,_).
