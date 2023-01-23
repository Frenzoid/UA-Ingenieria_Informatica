:- use_module('./pl-man-game/main').


do(use(left)) :- havingObject, see(normal, left, '|').
do(get(right)) :- see(normal,right, 'a').
do(move(left)) :- havingObject.
do(move(right)) :- see(normal,right, ' ').
