# Sabau Sabau, Elvi Mihai

INPUT = matriz.c
OUTPUT = matriz
OPTS = mpicc

all:
	${OPTS} ${INPUT} -o ${OUTPUT} -lm


clear: 
	rm ${OUTPUT}

redo: 
	rm ${OUTPUT} && ${OPTS} ${INPUT} -o ${OUTPUT} -lm
	
run:
	mpirun -np 16 ./${OUTPUT}