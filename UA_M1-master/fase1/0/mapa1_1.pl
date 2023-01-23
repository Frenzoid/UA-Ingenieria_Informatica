%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DIF:	5
%%% PT:	00:18	[STS: 00:54]
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

map_format_version(1.0).
load_behaviour(pushBlocks).
map([['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', ' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', '#', '#', '#', '#', '#', '.', '#', '#', '.', '#', '#', '.', '#', '#', '#', '.', '#', '#', '#', ' ', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'],
['#', ' ', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#', '#', '#', '.', '#', '#', '#'],
['#', ' ', '#', ' ', '.', '.', '.', '.', '#', ' ', '.', ' ', ' ', ' ', '.', ' ', ' ', '.', ' ', '.', '.', '#'],
['#', ' ', '.', '.', '#', ' ', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', ' ', '.', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]).
map_size(22, 8).
num_dots(70).
pacman_start(1, 1).
initMap:- 
	addSolidObject('#'), 
	createGameEntity(OID_P, '\\', object, 5, 6, inactive, norule, 
			[ name(palanca), solid(false), static(false), use_rule(pushBlocks), 
			  description('Barra grande con la que se pueden empujar grandes bloques'), appearance(attribs(bold, cyan, default)) ]),
	createGameEntity(OID_B1,'%', object, 18, 5, inactive, norule, 
			[ name(bloque1), solid(true), static(true), use_rule(norule), 
			  description('Bloque grande de hormigon'), appearance(attribs(bold, black, green)) ]),
	createGameEntity(OID_B2,'%', object, 18, 6, inactive, norule, 
			[ name(bloque2), solid(true), static(true), use_rule(norule), 
			  description('Bloque grande de hormigon'), appearance(attribs(bold, black, green)) ]),
	pushBlocks(init, OID_P, [OID_B1, OID_B2]).
norule(_).
norule(_,_,_,_,_).
