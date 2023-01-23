#! /bin/bash
# Author: Frenzoid

# First arg: path to the file to compile and execute.
# Second arg: number of processors to emulate.


execname=$(echo $1 | cut -f1 -d ".")
mpicc $1 -o $execname && mpirun -np $2 $execname
