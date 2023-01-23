:- use_module('./pl-man-game/main').


do(move(down)) :- see(normal,down,'.').
do(move(right)) :- see(normal,left,' '), see(normal,down, '#'), see(normal, right, '.'), see(normal, up-right,'#'), see(normal, up-left,' '), see(normal, down-right,'#'), see(normal, down-left,'#').
do(move(up)) :- see(normal,up,'.').
do(move(right)) :- see(normal,right,'.').
do(move(left)) :- see(normal,left,'.').

do(move(up)) :- see(normal,up-left,'.'), not(see(normal, up, '#')).
do(move(up)) :- see(normal,up-right,'.'), not(see(normal, up, '#')).
do(move(down)) :- see(normal,down-left,'.'), not(see(normal, down, '#')).
do(move(down)) :- see(normal,down-right,'.'), not(see(normal, down, '#')).


do(move(up)) :- see(normal,left,'#'), see(normal,down, '#'), see(normal, right, '#').
do(move(up)) :- see(normal,left,' '), not(see(normal,up, '#')), see(normal, right, '#').
do(move(left)) :- see(normal,left,' '), not(see(normal,left, '#')).
do(move(down)) :- see(normal,down,' '), not(see(normal,down, '#')).
