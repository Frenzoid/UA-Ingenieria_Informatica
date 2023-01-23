# Elvi Mihai Sabau Sabau - 51254875L

OPTS = -Wall -O3 -std=c++0x

make: maxsumbb

maxsumbb: maxsum-bb.cc
	g++ ${OPTS} -o maxsum-bb maxsum-bb.cc 

filter: filter.cc
	g++ ${OPTS} -o filter filter.cc

tar: maxsum-bb.cc makefile
	tar cvfz ${ENV_VAR_DNI}.tar.gz  maxsum-bb.cc makefile memoria.pdf