:- use_module('./pl-man-game/main').

do(move(left)) :- see(normal,left,'.').
do(get(left)) :- see(normal, left, 'a').
do(use(down)) :- see(normal, down, '-').
do(move(down)) :- see(normal,down,'.').
do(move(right)) :- see(normal,right,'.').
