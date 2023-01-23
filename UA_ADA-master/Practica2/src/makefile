# Elvi Mihai Sabau Sabau - 51254875L

OPTS = -Wall -O3 -std=c++0x

qs-vs-hs: qs-vs-hs.cc
	g++ ${OPTS} -o qs-vs-hs qs-vs-hs.cc	 

qs-vs-hs.Msteps: qs-vs-hs
	./qs-vs-hs > qs-vs-hs.Msteps

graphs: qs-vs-hs.Msteps qs-vs-hs.gnuplot
	gnuplot qs-vs-hs.gnuplot

all: qs-vs-hs qs-vs-hs.Msteps graphs

tar: qs-vs-hs.cc qs-vs-hs.gnuplot makefile
	tar cvfz ${ENV_VAR_DNI}.tar.gz qs-vs-hs.cc qs-vs-hs.gnuplot makefile

clean: 
	rm qs-vs-hs qs-vs-hs.Msteps fit.log *.png 
 
