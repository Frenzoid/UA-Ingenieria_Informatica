# Sabau Sabau, Elvi Mihai

INPUT = pimpi.c
OUTPUT = pimpi
OPTS = mpicc

all:
	${OPTS} ${INPUT} -o ${OUTPUT}


clear: 
	rm ${OUTPUT}

redo: 
	rm ${OUTPUT} && ${OPTS} ${INPUT} -o ${OUTPUT}
	
run:
	mpirun -np 4 ./${OUTPUT}