# Elvi Mihai Sabau - 51254875L

OPTS = -Wall -O3 -std=c++0x

quickSort: quickSort.cc
	g++ ${OPTS} -o quickSort quickSort.cc	 

quickSort.CPUtimes: quickSort
	./quickSort > quickSort.CPUtimes

graphs: quickSort.CPUtimes quickSort.gnuplot
	gnuplot quickSort.gnuplot

all: quickSort quickSort.CPUtimes graphs

tar: quickSort.cc quickSort.gnuplot makefile
	tar cvfz ${ENV_VAR_DNI}.tar.gz quickSort.cc quickSort.gnuplot makefile

clean: 
	rm quickSort quickSort.CPUtimes fit.log quickSort*.png *~
 
