.PHONY= doc clean

CC=g++
OPTIONS= -g -Wall -O0 -std=c++0x
DEBUG= # -D DEBUG
LIBDIR=lib
INCLUDEDIR=include
_OBJ= tcomplejo.o tvectorcom.o tabbcom.o 
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

main:    src/main.cpp $(OBJ)
	$(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) src/main.cpp $(OBJ) -o main

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -o $@ $<


tar: include lib src nombres.txt
	tar cvfz practica.tar.gz include/*.h lib/*cpp src/*.cpp nombres.txt

clean: lib/tlistacom.o lib/tvectorcom.o lib/tcomplejo.o 
	rm lib/*.o 

