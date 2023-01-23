:- use_module('./pl-man-game/main').

do(drop(right)) :- see(normal, left, 'r'), havingObject.
do(get(left)) :- see(normal, left, 'r'), not(havingObject).
do(get(right)) :- see(normal, right, 'a'), not(havingObject).

do(use(left)) :- see(normal, left, '|'), havingObject(appearance('r')).
do(use(down)) :- see(normal, down, '_'), havingObject(appearance('a')).

do(move(right)) :- see(normal, up, 'E'), havingObject.
do(move(right)) :- see(normal, down, 'E'), not(havingObject).


do(drop(right)) :- see(normal, right, ' '), see(normal, down, ' '), see(normal, left, ' '), see(normal, up, '#'), see(normal, down-left, '#'), see(normal, down-right, ' '), havingObject.
do(move(left)) :- see(normal, right, 'r'), see(normal, down, ' '), see(normal, left, ' '), see(normal, up, '#'), see(normal, down-left, '#'), see(normal, down-right, ' ').

do(move(up)) :- see(normal, up, '.').
do(move(right)) :- see(normal, right, '.').
do(move(down)) :- see(normal, down, '.').
do(move(left)) :- see(normal, left, '.').

do(move(down)) :- see(normal, down, ' ').
do(move(left)) :- see(normal, left, ' ').
do(move(up)) :- see(normal, up, ' ').
do(move(right)) :- see(normal, right, ' ').

