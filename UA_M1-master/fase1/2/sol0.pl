:- use_module('./pl-man-game/main').

do(move(none)) :- see(normal, down, 'E').

do(get(up)) :- see(normal,up,'O').
do(drop(right)) :- see(normal,left,'O'), not(see(normal,right,'O')).
do(get(left)) :- see(normal,left,'O'), see(normal,right,'O').

do(move(left)) :- see(normal,right,'O').

do(move(down)) :- see(normal,down,'.').
do(move(up)) :- see(normal,up,'.').
do(move(right)) :- see(normal,right,'.').
do(move(left)) :- see(normal,left,'.').

do(move(up)) :- see(normal,up-left,'.'), not(see(normal, up, '#')).
do(move(up)) :- see(normal,up-right,'.'), not(see(normal, up, '#')).
do(move(down)) :- see(normal,down-left,'.'), not(see(normal, down, '#')).
do(move(down)) :- see(normal,down-right,'.'), not(see(normal, down, '#')).

do(move(right)) :- see(normal, right, ' '), not(see(normal, right, '#')).
do(move(down)) :- see(normal, down, ' '), not(see(normal, down, '#')).
