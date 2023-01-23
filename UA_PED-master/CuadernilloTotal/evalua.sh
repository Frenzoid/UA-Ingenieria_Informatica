
ERRORS=0;
OKS=0;

# Si tus ficheros de prueba no comienzan por "tad", cambia "tad*.cpp" por el prefijo de tus ficheros, por ejemplo "prueba*.cpp":
for FILE in ../*PRUEBA/*.cpp ; do 
	echo "Evaluando $FILE"
	#Si tu Makefile espera que el fichero que contiene el programa principal se llame tad.cpp, cambia la siguiente línea por: cp $FILE src/tad.cpp
	cp $FILE src/main.cpp 
	make
	# *valgrind --track-origins=yes ./main &&
	./main > $FILE.out
	diff -b -B -i $FILE.out $FILE.sal
	if [ "$?" == "0" ]; then
		echo "OK"
		OKS=$(expr $OKS + 1);
	else
		echo "ERROR"
		ERRORS=$(expr $ERRORS + 1);
	fi
done

echo "|---------------------|"
echo "| Total Errors: $ERRORS";
echo "| Total Oks:    $OKS";
echo "|---------------------|"