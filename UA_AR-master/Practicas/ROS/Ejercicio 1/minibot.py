
__author__ = "Elvi Mihai Sabau Sabau"
__license__ = "GPL"
__version__ = "1.0.1"
__maintainer__ = "Elvi Mihai Sabau Sabau"
__email__ = "frenzoid@pm.me"

"""Este programa simulará un pequeño robot móvil que se encuentra en un punto de
una habitación de paredes paralelas dos a dos, saluda diciendo que es Minibot y que si
queremos escanear la habitación. En caso de que contestásemos que sí, nos pedirá cuatro
medidas del láser. Una vez hemos introducido las cuatro medidas mostrará como resultado
cuál es el largo y ancho de la habitación, la superficie total y la posición del robot en
coordenadas X, Y. En caso de que le contestemos que no, Minibot se despide y termina el
programa. Se ha de entregar el código fuente debidamente comentado."""


# Definimos las variables necesarias
escanear = ""
arriba = 0
abajo = 0
izquierda = 0
derecha = 0

# Saludamos.
print("Hola, soy Minibot")

# Preguntamos en bucle si queremos escanear la habitación, hasta recibir si o no.
while escanear != "si":
    escanear = input("¿Quieres escanear la habitación? (si / no): ")

    # Si queremos escanear la habitación.
    if escanear == "si":
        # Preguntamos cuantos metros hay por encima del robot.
        arriba = int(input("Introduce la medida del láser arriba: "))

        # Preguntamos cuantos metros hay por debajo del robot.
        abajo = int(input("Introduce la medida del láser abajo: "))

        # Preguntamos cuantos metros hay a la izquierda del robot.
        izquierda = int(input("Introduce la medida del láser izquierda: "))

        # Preguntamos cuantos metros hay a la derecha del robot.
        derecha = int(input("Introduce la medida del láser derecha: "))

        # Calculamos el largo y ancho de la habitación.
        print("El largo de la habitación es: ", arriba + abajo)
        print("El ancho de la habitación es: ", izquierda + derecha)

        # Calculamos la superficie total.
        print("La superficie total de la habitación es: ",
              (arriba + abajo) * (izquierda + derecha))

        # Calculamos la posición del robot.
        print("La posición del robot en coordenadas X, Y es:", izquierda, abajo)

    elif escanear == "no":
        # si no queremos escanear la habitación, nos despedimos y salimos.
        print("Adiós")
        exit()
    else:
        # si no es ni si ni no, se pregunta de nuevo.
        print("No te he entendido")
