# Supón que $t1=0x0000FACE, utilizando únicamente las instrucciones lógicas
# 	de la tabla anterior, escribe el código que reordene los bits de $t1 de manera que
# 	en $t2 aparezca el valor 0x0000CAFE. Ensambla y escribe en la ventana de
# 	registros $t1=0x0000FACE. Ejecuta y comprueba que el código es correcto.

.text

# Bueno.. mejor que suponer, lo guardamos para cuando lo usemos.
addi $t1, $zero, 0x0000FACE


# Primero vamos a ver que valores tienen en bin.
# 0000FACE = 0000 0000 0000 0000 1111 1010 1100 1110
# 0000CAFE = 0000 0000 0000 0000 1100 1010 1111 1110

# Parece que la opci�n m�s directa ser�a usando xor...

# 0000FACE xor 0000CAFE = 0000 0000 0000 0000 0011 0000 0011 0000 = 0003030
# Entoces 0000FACE xor 0003030 = 0000CAFE
xori $t2, $1, 0x0003030

# Salir del programa
addi $v0, $zero, 10 
syscall
