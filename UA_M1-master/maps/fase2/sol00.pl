:- use_module('./pl-man-game/main').

do(get(up)):-not(havingObject), see(normal,up,'r').
do(get(up)):-not(havingObject), see(normal,left,' '),see(normal,up,'a').
do(move(right)):-not(havingObject), see(normal,right,' ').
do(move(up)):-not(havingObject).

do(use(right)):-havingObject(appearance('a')), see(normal, right,'|').
do(drop(up)):-havingObject(appearance('a')), see(normal, left,'#'),see(normal, down,'#').
do(move(down)):-havingObject(appearance('a')), see(normal, left,'#').
do(move(left)):-havingObject(appearance('a')).
do(use(right)):-havingObject(appearance('r')), see(normal, right, '|').
do(move(right)):-havingObject(appearance('r')), see(normal, right, '.').
do(move(left)):-havingObject(appearance('r')), see(normal, left, ' ').
do(move(up)):-havingObject(appearance('r')).