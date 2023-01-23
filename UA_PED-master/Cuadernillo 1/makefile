.PHONY= doc clean

CC=g++
OPTIONS= -g -Wall -O3 -std=c++0x
DEBUG= # -D DEBUG
LIBDIR=lib
INCLUDEDIR=include
_OBJ= tcomplejo.o tvectorcom.o tlistacom.o 
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

main:    src/main.cpp $(OBJ)
	$(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) src/main.cpp $(OBJ) -o main

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<


tar: include lib src nombres.txt
	tar cvfz practica.tar.gz include/ lib/ src/ nombres.txt

clean: lib/tlistacom.o lib/tvectorcom.o lib/tcomplejo.o 
	rm lib/*.o 

