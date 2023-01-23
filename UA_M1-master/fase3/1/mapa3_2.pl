%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DIF:	1
%%% PT:	__:__	[STS: __:__]
%%%
%%% INDETERMINISMOS DE ESTE MAPA
%%%------------------------------------------------------------
%%% En este mapa los únicos objetos que pueden aparecer cambia-
%%% dos de posición son las llaves de la puerta semántica. En
%%% la sala inferior aparecen siempre 4 llaves, de las cuales
%%% 1 es correcta y 3 incorrectas. Las llaves pueden aparecer
%%% en cualquier punto de la sala, pero nunca aparecerán 2
%%% en el mismo sitio.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

map_format_version(1.0).
load_behaviour(enemyBasicMovement).
load_behaviour(basicDoorKey).
load_behaviour(arithmeticDoor).
map([['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#'],
['#', ' ', '¬', 'p', 'v', 'q', '-', '>', '¬', 'r', ' ', '#', '#', '#', ' ', '#', '#', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]).
map_size(18, 11).
num_dots(95).
pacman_start(1, 9).
initMap:- 
	msgWindowWriteln('¿Cuántas interpretaciones tiene la fbf?'),	
	msgWindowWriteln('El número correcto te abrirá la puerta semántica'),
	msgWindowWriteln('Los números aparecerán en 4 posiciones aleatorias'),
	addSolidObject('#'), 
	% Puerta y llaves
	% Las llaves (1,2,4,8) aparecen en cuatro posiciones aleatorias, cada uno dentro de una de las
	% cuatro zonas de cocos en que se divide la parte inferior (de izda a dcha)
	createGameEntity(OID_0, '*', object, 14, 5, inactive, norule, 
			[name('puerta_semantica'), solid(true), static(true), use_rule(norule),
			description('Puerta Semántica'), appearance(attribs(normal, red, cyan))]), 
	createGameEntity(    _, 1, object, rnd(2,4), rnd(7,9), inactive, norule, 
			[name('1'), solid(false), static(false), use_rule(basicDoorKey),
			description('Una interpretación'), appearance(attribs(bold, cyan, default))]), 
	createGameEntity(    _, 2, object, rnd(5,8), rnd(7,9), inactive, norule, 
			[name('2'), solid(false), static(false), use_rule(basicDoorKey),
			description('Dos interpretaciones'), appearance(attribs(bold, cyan, default))]), 
	createGameEntity(    _, 4, object, rnd(9,12), rnd(7,9), inactive, norule, 
			[name('4'), solid(false), static(false), use_rule(basicDoorKey),
			description('Cuatro interpretaciones'), appearance(attribs(bold, cyan, default))]), 
	createGameEntity(OID_4, 8, object, rnd(13,16), rnd(7,9), inactive, norule, 
			[name('8'), solid(false), static(false), use_rule(basicDoorKey),
			description('Ocho interpretaciones'), appearance(attribs(bold, cyan, default))]), 
	basicDoorKey(init, OID_0, ['pl-man':destroyGameEntity(OID_0), 'pl-man':msgWindowWriteln('Correcto, son 8. Puedes pasar')],  [OID_4]),
	% Enemigo	
	createGameEntity(EID_0, 'E', mortal, 9, 2, active, enemyBasicMovement, [appearance(attribs(bold, red, default))]),
	enemyBasicMovement(init, EID_0, left-right, ['#']).

norule(_).
norule(_,_,_,_,_).
