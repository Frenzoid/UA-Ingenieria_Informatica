%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DIF:	4
%%% PT:	02:00	[STS: 08:00]
%%%
%%% INDETERMINISMOS DE ESTE MAPA
%%%------------------------------------------------------------
%%% Este mapa cuenta con 3 factores indeterministas que se
%%% describen a continuación:
%%% 1) Posición inicial de PL-MAN:
%%%      PL-MAN aparece en cualquier posición aleatoria de
%%%      todo el mapa, siempre separado almenos 1 posición
%%%      de todas las paredes.
%%% 2) Posición inicial de los fantasmas:
%%%      Los 5 fantasmas aparecen en 5 posiciones aleatorias y
%%%      diferentes en todo el mapa. Nunca pueden aparecer
%%%      a menos de 1 casilla de distancia de PL-MAN.
%%% 3) Comportamiento de los fantamas:
%%%      Los fantasmas eligen una dirección aleatoria en la que
%%%      moverse y la siguen hasta llegar a una pared. Cuando
%%%      llegan a la pared, cambian aleatoriamente de dirección
%%%      y repiten. Si por el camino, yendo de pared a pared,
%%%      ven a PL-MAN en alguna dirección, cambian su dirección
%%%      de movimiento para seguir a PL-MAN con una probabilidad
%%%      del 75%. Nunca cambian de dirección más de 2 veces
%%%      entre pared y pared que tocan.
%%%
%%% El resto de elementos de este mapa son deterministas.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

map_format_version(1.0).
load_behaviour(spiderGhost).
map([['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', ' ', ' ', ' ', ' ', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', ' ', ' ', ' ', ' ', '#'],
['#', ' ', ' ', ' ', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', ' ', ' ', ' ', '#'],
['#', ' ', ' ', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', ' ', ' ', '#'],
['#', ' ', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', ' ', '#'],
['#', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', '#'],
['#', ' ', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', ' ', '#'],
['#', ' ', ' ', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', ' ', ' ', '#'],
['#', ' ', ' ', ' ', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', ' ', ' ', ' ', '#'],
['#', ' ', ' ', ' ', ' ', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', ' ', ' ', ' ', ' ', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]).
map_size(38, 13).
num_dots(336).
pacman_start(X, Y):- randomBetween(2,35, X), randomBetween(2,10, Y).
initMap:- 
	addSolidObject('#'),
	entityType(PACID, pacman),
	entityLocation(PACID, PX, PY, _),
	% SPIDER GHOSTS
	forall(between(1,5,_),
	(
		repeat,
		(randomBetween(1,36,X), randomBetween(1,11,Y)),
		not((X >= PX-1, X =< PX+1, Y >= PY-1, Y =< PY+1)),
		not(entityLocation(_, X, Y, _)),
		createGameEntity(EID, 'F', mortal, X, Y, active, spiderGhost,
			[appearance(attribs(normal, red, default))]),
		spiderGhost(init, EID, ['#'], [ probFollowPacman(65), maxFollowTimes(2) ])
	)).

norule(_).
norule(_,_,_,_,_).
