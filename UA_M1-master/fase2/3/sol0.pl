:- use_module('./pl-man-game/main').


do(move(none)) :- see(normal, right-up, 'E').
do(move(none)) :- see(normal, left-down, 'E').

do(move(up)) :- see(normal, left, 'E'), see(normal, right-down, '+').

do(move(left)) :- see(normal, up, 'E'), see(normal, down, '#') .
do(move(down)) :- see(normal, up, 'E').
do(move(up)) :- see(normal, down, 'E').
do(move(right)) :- see(normal, left, 'E').
do(move(left)) :- see(normal, right, 'E').

do(move(down)) :- see(normal, right, '#'), see(normal, right-up, '#'), see(normal, down, '.').
do(move(right)) :- see(normal, right, '.'), see(normal, right-up, ' '), see(normal, down, ' '), see(normal, left, '.'), see(normal, left-down, '#'), see(normal, up, ' '), see(normal, right-up, ' ').
do(move(left)) :- see(normal, left, ' '), see(normal, right, ' '), see(normal, down, ' '), see(normal, up, ' ').
do(move(left)) :- see(normal, right, ' '), see(normal, right-up, ' '), see(normal, down, ' '), see(normal, left, '.'), see(normal, left-down, '#').


do(get(up)) :- see(normal, up, '+').
do(drop(down)) :- see(normal, down-right, '|'), havingObject.

do(move(down)) :- see(normal,down,'.'), havingObject.
do(move(right)) :- see(normal,right,'.'), havingObject.
do(move(up)) :- see(normal,up,'.'), havingObject.
do(move(left)) :- see(normal,left,'.'), havingObject.

do(move(up)) :- see(normal,up,'.').
do(move(left)) :- see(normal,left,'.').
do(move(right)) :- see(normal,right,'.').
do(move(down)) :- see(normal,down,'.').

do(move(right)) :- see(normal, down, '#'), see(normal, right, ' '),see(normal, left, ' '),see(normal, up, ' ').

do(move(down)) :- see(normal,down,' ').
do(move(left)) :- see(normal,left,' ').
do(move(right)) :- see(normal,right,' ').
do(move(up)) :- see(normal,up,' ').
