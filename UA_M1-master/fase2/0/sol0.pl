:- use_module('./pl-man-game/main').

do(move(none)) :- see(normal, up-right, '|'), see(normal, up, '#').
do(move(none)) :- see(normal, right, '|').

do(move(left)) :- see(normal, right, 'E'),  see(normal, up, 'E').
do(move(none)) :- see(normal, down-left, 'E').
do(move(none)) :- see(normal, down-right, 'E').
do(move(up)) :- see(normal, right, 'E'), see(normal, up-right, ' ').
do(move(none)) :- see(normal, right, 'E'), see(normal, up, ' ').


do(get(down)) :- see(normal, down, 'l').

do(use(right)) :- see(normal, right, 'E').
do(use(left)) :- see(normal, left, 'E'), not(see(normal, up, '#')), not(see(normal, down, '#')), not(see(normal, down-left,'.')).

do(move(up)) :- see(normal,up,'.').
do(move(down)) :- see(normal,down,'.').
do(move(left)) :- see(normal,left,'.').
do(move(right)) :- see(normal,right,'.').

do(move(up)) :- see(normal,up-left,'.'), not(see(normal, up, '#')).
do(move(up)) :- see(normal,up-right,'.'), not(see(normal, up, '#')).
do(move(down)) :- see(normal,down-left,'.'), not(see(normal, down, '#')), not(see(normal, down, 'E')).
do(move(down)) :- see(normal,down-right,'.'), not(see(normal, down, '#')), not(see(normal, down, 'E')).

do(move(down)) :- see(normal, down, ' '), not(see(normal, down, '#')), not(see(normal, down, 'E')).
do(move(up)) :- see(normal, down, ' '), not(see(normal, up, '#')).
do(move(right)) :- see(normal, right, ' '), not(see(normal, right, '#')).