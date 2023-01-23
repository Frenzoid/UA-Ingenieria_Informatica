%%%%%%%%%%%%%%%%%%%%%%%%% EXAM MAP %%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DIF:	2
%%% PT:	00:20	[STS: 01:15]
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:- dynamic d_balls/1.

map_format_version(1.0).
load_behaviour(launchBall).
load_behaviour(soccerGoal).
load_behaviour(entitySequentialMovement).
map([['#', '#', '#', '#', '#', '#', '#', '#', '\\', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
[' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '/', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]).
map_size(19, 5).
num_dots(24).
pacman_start(1, 2).
initMap:- 
	addSolidObject('#'), 
	addSolidObject('\\'), 
	addSolidObject('/'), 
	createGameEntity(OID_M, '0', object, 0, 2, active, soccerGoal,
			[ name(marcador), solid(true), static(true), use_rule(norule),
			  description('Marcador de goles acumulados'), appearance(attribs(bold, yellow, green))]), 
	createGameEntity(OID_P1, '|', object, 9, 1, inactive, norule, 
			[ name(porteria), solid(true), static(true), use_rule(norule),
			  description('Red de la porteria'), appearance(attribs(bold, green, green))]), 
	createGameEntity(OID_P2, '|', object, 9, 2, inactive, norule, 
			[ name(porteria), solid(true), static(true), use_rule(norule),
			  description('Red de la porteria'), appearance(attribs(bold, green, green))]), 
	createGameEntity(OID_P3, '|', object, 9, 3, inactive, norule, 
			[ name(porteria), solid(true), static(true), use_rule(norule),
			  description('Red de la porteria'), appearance(attribs(bold, green, green))]), 
	createGameEntity(EID_E, 'E', mortal, 8, 2, active, entitySequentialMovement, [ appearance(attribs(normal, red, default)) ]),
	soccerGoal(init, OID_M, 3, ['o'], [OID_P1, OID_P2, OID_P3], []),
	entitySequentialMovement(init, EID_E, [n, n, n, n, n, n, n, n, n, u, n, d, n, n, n, n, n, n, n, n, d, n, u], []),
	launchBall(autoBallCreator, 1, 7, 2, 2).

norule(_).
norule(_,_,_,_,_).
