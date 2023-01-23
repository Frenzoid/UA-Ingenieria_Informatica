# Elvi Mihai Sabau Sabau

import pygame
import tkinter
import tkinter.filedialog

from Casilla import Casilla
from Mapa import Mapa
from AStar import AStar
from heuristicas import uniforme
from heuristicas import euclidea
from heuristicas import manhattan
from heuristicas import chebyshev
from heuristicas import frioCaliente
from pygame.locals import *


MARGEN = 5
MARGEN_INFERIOR = 60
TAM = 15
NEGRO = (0, 0, 0)
BLANCO = (255, 255, 255)
VERDE = (0, 255, 0)
ROJO = (255, 0, 0)
AZUL = (0, 0, 255)
AMARILLO = (255, 255, 0)

# ---------------------------------------------------------------------

# Funciones
# ---------------------------------------------------------------------

# Devuelve si una casilla del mapa se puede seleccionar como destino


def bueno(mapa, pos):
    res = False

    if mapa.getCelda(pos.getFila(), pos.getCol()) == 0:
        res = True

    return res

# Devuelve si una posición de la ventana corresponde al mapa


def esMapa(mapa, posicion):
    res = False

    if posicion[0] > MARGEN and posicion[0] < mapa.getAncho()*(TAM+MARGEN)+MARGEN and \
            posicion[1] > MARGEN and posicion[1] < mapa.getAlto()*(TAM+MARGEN)+MARGEN:
        res = True

    return res

# PDevuelve si se ha pulsado el botón. Posición del botón: 20, mapa.getAlto()*(TAM+MARGEN)+MARGEN+10]


def pulsaBoton(mapa, posicion):
    res = False

    if posicion[0] > 20 and posicion[0] < 70 and \
       posicion[1] > mapa.getAlto()*(TAM+MARGEN)+MARGEN+10 and posicion[1] < MARGEN_INFERIOR+mapa.getAlto()*(TAM+MARGEN)+MARGEN:
        res = True

    return res


# Construye la matriz para guardar el camino
def inic(mapa):
    cam = []
    for i in range(mapa.alto):
        cam.append([])
        for _ in range(mapa.ancho):
            cam[i].append('.')

    return cam


# función principal
def main():
    root = tkinter.Tk()  # para eliminar la ventana de Tkinter
    root.withdraw()  # se cierra
    file = tkinter.filedialog.askopenfilename()  # abre el explorador de archivos

    pygame.init()
    destino = Casilla(-1, -1)

    reloj = pygame.time.Clock()

    if not file:  # si no se elige un fichero coge el mapa por defecto
        file = '../Mundos/mapa.txt'

    mapa = Mapa(file)
    origen = mapa.getOrigen()
    camino = inic(mapa)

    anchoVentana = mapa.getAncho()*(TAM+MARGEN)+MARGEN
    altoVentana = MARGEN_INFERIOR+mapa.getAlto()*(TAM+MARGEN)+MARGEN
    dimension = [anchoVentana, altoVentana]
    screen = pygame.display.set_mode(dimension)
    pygame.display.set_caption("A*")

    boton = pygame.image.load("./assets/boton.png").convert()
    boton = pygame.transform.scale(boton, [50, 30])

    personaje = pygame.image.load("./assets/pig.png").convert()
    personaje = pygame.transform.scale(personaje, [TAM, TAM])

    coste = -1
    running = True
    primeraVez = True

    while running:
        # procesamiento de eventos
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            if event.type == pygame.MOUSEBUTTONDOWN:
                # obtener posición y calcular coordenadas matriciales
                pos = pygame.mouse.get_pos()
                colDestino = pos[0] // (TAM + MARGEN)
                filDestino = pos[1] // (TAM + MARGEN)
                casilla = Casilla(filDestino, colDestino)
                if pulsaBoton(mapa, pos):  # reinicializar
                    origen = mapa.getOrigen()
                    destino = Casilla(-1, -1)
                    camino = inic(mapa)
                    coste = -1
                    primeraVez = True
                elif esMapa(mapa, pos):
                    if bueno(mapa, casilla):
                        if not primeraVez:  # la primera vez el origen está en el mapa
                            origen = destino
                        else:
                            # se marca como libre la celda origen
                            mapa.setCelda(int(origen.getFila()),
                                          int(origen.getCol()), 0)
                        destino = casilla
                        camino = inic(mapa)

                        # llamar al A*
                        # Para el profesor: para cambiar la heuristica, solo hay que cambiar 'manhattan' por 'uniforme' o el nombre de la euristica a usar al llamar a AStar.
                        coste = AStar(
                            mapa, origen, destino, camino, uniforme)

                        if coste == -1:
                            tkinter.messagebox.showwarning(
                                title='Error', message='Theres no way between the start and the end point.')
                        else:
                            primeraVez = False  # hay un camino y el destino será el origen para el próximo movimiento
                    else:  # se ha hecho click en una celda roja
                        tkinter.messagebox.showwarning(
                            title='Error', message='This slot is invalid.')

        # código de dibujo
        # limpiar pantalla
        screen.fill(NEGRO)
        # pinta mapa

        for fil in range(mapa.getAlto()):
            filastring = ''

            for col in range(mapa.getAncho()):

                # Por cada tick, pinta el mapa y pinta en azul las casillas exploradas, y imprime en consola los caminos
                if mapa.getCelda(fil, col) == 2 and not primeraVez:
                    pygame.draw.rect(screen, BLANCO, [
                                     (TAM+MARGEN)*col+MARGEN, (TAM+MARGEN)*fil+MARGEN, TAM, TAM], 0)
                    filastring += '-1'.rjust(4)
                if mapa.getCelda(fil, col) == 0:
                    if camino[fil][col] == '.':
                        pygame.draw.rect(screen, BLANCO, [
                                         (TAM+MARGEN)*col+MARGEN, (TAM+MARGEN)*fil+MARGEN, TAM, TAM], 0)
                        filastring += '-1'.rjust(4)
                    elif camino[fil][col][0] == 1:
                        pygame.draw.rect(screen, AZUL, [
                                         (TAM+MARGEN)*col+MARGEN, (TAM+MARGEN)*fil+MARGEN, TAM, TAM], 0)
                        filastring += str(camino[fil][col][1]).rjust(4)
                    elif camino[fil][col][0] == 0:
                        pygame.draw.rect(screen, AMARILLO, [
                                         (TAM+MARGEN)*col+MARGEN, (TAM+MARGEN)*fil+MARGEN, TAM, TAM], 0)
                        filastring += ('[' + str(camino[fil]
                                       [col][1]) + ']').rjust(4)

                elif mapa.getCelda(fil, col) == 1:
                    pygame.draw.rect(
                        screen, ROJO, [(TAM+MARGEN)*col+MARGEN, (TAM+MARGEN)*fil+MARGEN, TAM, TAM], 0)
                    filastring += '-1'.rjust(4)
                else:
                    filastring += '-1'.rjust(4)

            print(filastring)

        print("--------------------------------------------------")

        # pinta origen
        screen.blit(personaje, [(TAM+MARGEN)*origen.getCol() +
                                MARGEN, (TAM+MARGEN)*origen.getFila()+MARGEN])
        # pinta destino
        pygame.draw.rect(screen, VERDE, [
                         (TAM+MARGEN)*destino.getCol()+MARGEN, (TAM+MARGEN)*destino.getFila()+MARGEN, TAM, TAM], 0)
        # pinta boton
        screen.blit(boton, [20, mapa.getAlto()*(TAM+MARGEN)+MARGEN+10])
        # pinta coste
        if coste != -1:
            fuente = pygame.font.Font(None, 30)
            texto = fuente.render("Cost "+str(coste), True, AMARILLO)
            screen.blit(texto, [anchoVentana-120,
                                mapa.getAlto()*(TAM+MARGEN)+MARGEN+15])

        # actualizar pantalla
        pygame.display.flip()
        reloj.tick(40)

    pygame.quit()


# ---------------------------------------------------------------------
if __name__ == "__main__":
    main()
