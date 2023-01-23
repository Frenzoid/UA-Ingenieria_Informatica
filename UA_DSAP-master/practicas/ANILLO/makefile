# Sabau Sabau, Elvi Mihai

INPUT = anillo.c
OUTPUT = anillo
OPTS = mpicc

all:
	${OPTS} ${INPUT} -o ${OUTPUT}


clear: 
	rm ${OUTPUT}

redo: 
	rm ${OUTPUT} && ${OPTS} ${INPUT} -o ${OUTPUT}
	
run:
	mpirun -np 4 ${OUTPUT}