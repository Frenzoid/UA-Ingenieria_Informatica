# Elvi Mihai Sabau Sabau - 51254875L

OPTS = -Wall -O3 -std=c++0x

make: all

pow2: pow2.cc
	g++ ${OPTS} -o pow2 pow2.cc 

pow2.execute: pow2
	./pow2 > pow2.log

graphs: pow2.log pow2.gnuplot
	gnuplot pow2.gnuplot

all: pow2 pow2.execute graphs

tar:  pow2.cc pow2.gnuplot makefile
	tar cvfz ${ENV_VAR_DNI}.tar.gz  pow2.cc pow2.gnuplot makefile

clean: 
	rm pow2 *.log *.png 