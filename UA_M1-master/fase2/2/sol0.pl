:- use_module('./pl-man-game/main').


do(move(left)) :- see(normal, down-left, 'E'), not(see(normal,left,'#')), not(see(normal, right, '#')).
do(move(right)) :- see(normal, down, 'E'), not(see(normal,left,'#')).
do(move(right)) :- see(normal, down, 'E'), not(see(normal,left,'#')).
do(move(down)) :- see(normal, left, 'E'), not(see(normal,right,'#')).
do(move(down)) :- see(normal, up, 'E'), not(see(normal,down,'#')).
do(move(down)) :- see(normal, down-left, 'E'), not(see(normal,down,'#')).

do(get(right)) :- see(normal, right, 'a').
do(use(left)) :- see(normal, left, '|').

do(move(left)) :- see(normal,up,'.'), see(normal, up-right, '#'), see(normal, right, ' '), see(normal, down, '#').
do(move(up)) :- see(normal,up,'.').
do(move(down)) :- see(normal,down,'.').
do(move(left)) :- see(normal,left,'.'), not(see(normal, up-left, 'E')).
do(move(right)) :- see(normal,right,'.').

do(move(up)) :- see(normal,up-left,'.'), not(see(normal, up, '#')).
do(move(up)) :- see(normal,up-right,'.'), not(see(normal, up, '#')).
do(move(down)) :- see(normal,down-left,'.'), not(see(normal, down, '#')), not(see(normal, down, 'E')).
do(move(down)) :- see(normal,down-right,'.'), not(see(normal, down, '#')), not(see(normal, down, 'E')).

do(move(down)):- see(normal, left, 'E'), see(normal, right, '#').
do(move(down)):- see(normal, right, '#'), see(normal, left, ' '),  not(see(normal, down, '#')).
do(move(left)):- see(normal, down, '#'), not(see(normal, left, '#')), not(see(normal, up-left, 'E')).
do(move(up)) :- not(see(normal, up, '#')).
do(move(right)):- not(see(normal, right, '#')).
