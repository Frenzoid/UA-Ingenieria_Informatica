:- use_module('./pl-man-game/main').


do(move(up)) :- see(normal, down, 'E'), not(see(normal,up,'#')).
do(move(left)) :- see(normal, down, 'E'), not(see(normal,left,'#')).
do(move(right)) :- see(normal, left, 'E'), not(see(normal,right,'#')).
do(move(down)) :- see(normal, up, 'E'), not(see(normal,down,'#')).
do(move(down)) :- see(normal, down-left, 'E'), not(see(normal,down,'#')).

do(move(up)) :- see(normal,up,'.').
do(move(down)) :- see(normal,down,'.').
do(move(left)) :- see(normal,left,'.').
do(move(right)) :- see(normal,right,'.').

do(move(up)) :- see(normal,up-left,'.'), not(see(normal, up, '#')).
do(move(up)) :- see(normal,up-right,'.'), not(see(normal, up, '#')).
do(move(down)) :- see(normal,down-left,'.'), not(see(normal, down, '#')), not(see(normal, down, 'E')).
do(move(down)) :- see(normal,down-right,'.'), not(see(normal, down, '#')), not(see(normal, down, 'E')).

do(move(left)) :- see(normal, left, ' '), not(see(normal, left, '#')).
do(move(left)) :- see(normal, left, ' '), not(see(normal, left, '#')), see(nomal, up-right, '#').
do(move(up)) :- see(normal, down, ' '), not(see(normal, up, '#')).
do(move(right)) :- see(normal, right, ' '), see(normal, down, '#'), not(see(normal, right, '#')).
do(move(down)) :- see(normal, down, ' '), not(see(normal, down, '#')), not(see(normal, down, 'E')).