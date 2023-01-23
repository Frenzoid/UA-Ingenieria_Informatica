%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DIF:	5
%%% PT:	00:55	[STS: 02:45]
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

map_format_version(1.0).
load_behaviour(automaticArcher).
load_behaviour(entitySequentialMovement).
load_behaviour(gunBasic).
map([['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', '.', '.', '.', '.', '#', ' ', '#', ' ', '#', ' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', ' ', '#', ' ', '#', ' ', '#', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]).
map_size(54, 6).
num_dots(119).
pacman_start(1, 2).
initMap:- 
	addSolidObject('#'), 
	createGameEntity(OID_AR1, 'v', object, 6, 1, active, automaticArcher, 
	                 [name('Arquero 1'), solid(false), static(true), use_rule(norule),
			  description('Arquero de defensa lateral'), appearance(attribs(bold, yellow, default))]), 
	createGameEntity(OID_AR2, 'v', object, 8, 1, active, automaticArcher, 
	                 [name('Arquero 2'), solid(false), static(true), use_rule(norule),
			  description('Arquero de defensa lateral'), appearance(attribs(bold, yellow, default))]), 
	createGameEntity(OID_AR3, 'v', object, 10, 1, active, automaticArcher, 
	                 [name('Arquero 3'), solid(false), static(true), use_rule(norule),
			  description('Arquero de defensa lateral'), appearance(attribs(bold, yellow, default))]), 
	createGameEntity(OID_AR4, '^', object, 12, 3, active, automaticArcher, 
	                 [name('Arquero 4'), solid(false), static(true), use_rule(norule),
			  description('Arquero de defensa lateral'), appearance(attribs(bold, yellow, default))]), 
	createGameEntity(OID_AR5, '^', object, 14, 3, active, automaticArcher, 
	                 [name('Arquero 5'), solid(false), static(true), use_rule(norule),
			  description('Arquero de defensa lateral'), appearance(attribs(bold, yellow, default))]), 
	createGameEntity(OID_AR6, '^', object, 16, 3, active, automaticArcher, 
	                 [name('Arquero 6'), solid(false), static(true), use_rule(norule),
			  description('Arquero de defensa lateral'), appearance(attribs(bold, yellow, default))]), 
	createGameEntity(OID_GUN, 'l', object, 18, 3, inactive, norule, 
	                 [name(revolver), solid(false), static(false), use_rule(gunBasic),
			  description('Revolver colt-42'), appearance(attribs(bold, cyan, default))]), 
	createGameEntity(EID_E1, 'E', mortal, 20, 1, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]), 
	createGameEntity(EID_E2, 'E', mortal, 29, 1, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]),
	createGameEntity(EID_E3, 'E', mortal, 46, 1, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]),
	createGameEntity(EID_E4, 'E', mortal, 21, 2, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]),
	createGameEntity(EID_E5, 'E', mortal, 28, 2, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]),
	createGameEntity('E', mortal, 37, 2, active, norule, [appearance(attribs(normal, red, default))]),
	createGameEntity('E', mortal, 43, 2, active, norule, [appearance(attribs(normal, red, default))]),
	createGameEntity('E', mortal, 48, 2, active, norule, [appearance(attribs(normal, red, default))]),
	createGameEntity('E', mortal, 52, 2, active, norule, [appearance(attribs(normal, red, default))]),
	createGameEntity(EID_E6, 'E', mortal, 22, 3, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]),
	createGameEntity(EID_E7, 'E', mortal, 27, 3, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]),
	createGameEntity(EID_E8, 'E', mortal, 41, 3, active, entitySequentialMovement, [appearance(attribs(normal, red, default))]),
	gunBasic(init, OID_GUN, 4, ['E', '|', 'v', '^'], destroy),
	entitySequentialMovement(init, EID_E1, [ l,n,d,d,n,r,r,n,u,u,n,l ], []),
	entitySequentialMovement(init, EID_E2, [ r,n,d,d,n,l,l,n,u,u,n,r ], []),
	entitySequentialMovement(init, EID_E3, [ r,r,r,r,r,r,n,l,l,l,l,l,l,l,l,l,l,l,l,l,l,l,l,l,l,l,l,r,r,r,r,r,r,r,r,r,r,r,r,r,r ], []),
	entitySequentialMovement(init, EID_E4, [ l,l,r,r,r,r,r,r,r,r,r,r,r,r,n,n,l,l,l,l,l,l,l,l,l,l ], []),
	entitySequentialMovement(init, EID_E5, [ l,l,l,l,l,l,l,l,l,r,r,r,r,r,r,r,r,r,r,r,r,n,n,l,l,l ], []),
	entitySequentialMovement(init, EID_E6, [ u,u,n,r,r,n,d,d,n,l,l,n ], []),
	entitySequentialMovement(init, EID_E7, [ u,u,n,l,l,n,d,d,n,r,r,n ], []),
	entitySequentialMovement(init, EID_E8, [ l,l,l,l,l,l,l,l,l,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,r,n,l,l,l,l,l,l,l,l,l,l,l ], []),
	automaticArcher(init, OID_AR1, ['@'], down, 4, [ continuous, bullet_appearance('|', normal, red, default) ]),
	automaticArcher(init, OID_AR2, ['@'], down, 5, [ continuous, bullet_appearance('|', normal, red, default) ]),
	automaticArcher(init, OID_AR3, ['@'], down, 6, [ continuous, bullet_appearance('|', normal, red, default) ]),
	automaticArcher(init, OID_AR4, ['@'], up, 4, [ continuous, bullet_appearance('|', normal, red, default) ]),
	automaticArcher(init, OID_AR5, ['@'], up, 3, [ continuous, bullet_appearance('|', normal, red, default) ]),
	automaticArcher(init, OID_AR6, ['@'], up, 2, [ continuous, bullet_appearance('|', normal, red, default) ]).

norule(_).
norule(_,_,_,_,_).
