:- use_module('./pl-man-game/main').

do(move(down)) :- see(normal,right, '#').
do(move(down)) :- see(normal,down,'.').
do(move(up)) :- see(normal, right, '#').
do(move(left)) :- see(normal,left,'.').
do(move(right)) :- see(normal,right,'.').