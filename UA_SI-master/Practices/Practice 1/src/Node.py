# Elvi Mihai Sabau Sabau

class Node():
    """A Node class, used to encapsulate each slot (Casilla) and assign them the g, h and f value"""

    def __init__(self, parent=None, slot=None):
        self.parent = parent
        self.slot = slot

        # Distance from start point
        self.g = 0

        # Distance prediction until end point
        self.h = 0

        # Total distance.
        self.f = 0

        # Node number, used to enumerate paths.
        self.number = 0

    # Overload of operator ==
    def __eq__(self, otro):
        return self.slot == otro.slot

    # Hash method, we need this one so we can use sets.
    def __hash__(self):
        return self.slot.__hash__()
