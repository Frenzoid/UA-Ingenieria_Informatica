:- use_module('./pl-man-game/main').

do(move(left)) :- see(normal,left,'.').
do(get(left)) :- see(normal, left, 'U').
do(get(left)) :- see(normal, right, 'U').
do(drop(right)) :- see(normal, left, 'V').
