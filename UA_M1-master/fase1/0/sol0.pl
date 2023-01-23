:- use_module('./pl-man-game/main').

do(get(down)) :- see(normal, down, '\\').
do(use(right)) :- see(normal,up-right,'%'), see(normal,right,'%').
do(move(down)) :- see(normal,up,'%'), see(normal,right,'#'), see(normal, left, '#').
do(use(up)) :- see(normal, up, '%').

do(move(up)) :- see(normal,up,'.').
do(move(right)) :- see(normal,right,'.').
do(move(left)) :- see(normal,left,'.').
do(move(down)) :- see(normal,down,'.').
do(move(down)) :- see(normal,down,' ').
do(move(right)) :- see(normal,right,' ').
do(move(up)) :- see(normal,up,' ').

do(move(up)) :- see(normal,up,'.').
do(move(left)) :- see(normal,left,' ').





