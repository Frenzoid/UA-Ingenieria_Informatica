%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% DIF:	2+
%%% PT:	00:08	[STS: 00:24]
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

map([['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ' ', '#'],
['#', '.', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'],
['#', '.', '#', '.', '.', '.', '#', '.', ' ', ' ', '#', '#', '#', '#', '#'],
['#', '.', '.', '.', '#', '.', '.', '.', '#', ' ', ' ', ' ', ' ', '.', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'],
['#', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '.', '#', '.', '#'],
['#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'],
['#', '.', '.', '.', '.', '.', '.', ' ', '.', '.', '.', '.', '.', '.', '#'],
['#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#']]).
map_size(15, 10).
num_dots(43).
pacman_start(13, 1).
initMap:- 
	addSolidObject('#'), 
	createGameEntity('O', object, 3, 2, inactive, norule, 
			[ name(florecilla), solid(false), static(false), use_rule(norule), 
			description('Orquidea rarisima en peligro de extincion'), appearance(attribs(bold, yellow, default)) ]), 
	createGameEntity('O', object, 7, 8, inactive, norule, 
			[ name(floripondio), solid(false), static(false), use_rule(norule), 
			description('Orquidea mas rara todavia en peligro de extincion'), appearance(attribs(bold, yellow, default)) ]), 
	createGameEntity('E', mortal, 2, 2, active, vigilaFantasma, [ appearance(attribs(normal, red, default)) ]),
	retractall(next_movement(_,_)).
norule(_).

:-dynamic next_movement/2.

vigilaFantasma(EID):-
	not(next_movement(EID, _)),
	assert(next_movement(EID, right)),!.

vigilaFantasma(EID):-
	next_movement(EID, X),
	(
	 X=right,
	 see(EID,normal,X,'#')
	 ->
	  retractall(next_movement(EID, _)),
	  assert(next_movement(EID, left)),
	  asserta(d_doAction(EID,move(left)))
	 ;	
	 (
	  X=left,
	  see(EID,normal,X,'#')
	  ->
	   retractall(next_movement(EID, _)),
	   assert(next_movement(EID, right)),
	   asserta(d_doAction(EID,move(right)))
	 )
	 ;
	 (
	  asserta(d_doAction(EID,move(X)))
	 )).
	
