# Elvi Mihai Sabau Sabau

# heuristicas.py
def uniforme(actual, destino):
    return 0

# Uno es optimo y manhattan no, por la perdida de admisibilidad.


def manhattan(actual, destino):
    return abs(actual.getFila() - destino.getFila()) + abs(actual.getCol() - destino.getCol())


def euclidea(actual, destino):

    dx = abs(actual.getFila() - destino.getFila()) ** 2
    dy = abs(actual.getCol() - destino.getCol()) ** 2

    return (dx * dx + dy * dy) ** (1/2)


def chebyshev(actual, destino):
    dx = abs(actual.getFila() - destino.getFila())
    dy = abs(actual.getCol() - destino.getCol())

    return max(dx, dy)


def frioCaliente(actual, destino):
    dx = actual.getFila() + destino.getFila()
    dy = actual.getCol() + destino.getCol()

    return dx + dy
