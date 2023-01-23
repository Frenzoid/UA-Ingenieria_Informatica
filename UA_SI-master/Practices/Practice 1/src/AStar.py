# Elvi Mihai Sabau Sabau

import time

from Node import Node
from Casilla import Casilla


def AStar(map, start_slot, end_slot, path, heuristic):
    """A path-finding algorithm that maps all best paths from any end point to the start point."""

    # Create the start and end nodes.
    start_node = Node(None, start_slot)
    end_node = Node(None, end_slot)

    # We also create our discovered (open set) and checked (closed set).
    # Nodes that are discovered when looking for neighbor slots.
    discovered = set()
    # Nodes that are checked and aren't the end node.
    checked = set()

    # Add our start node to our discovered set.
    discovered.add(start_node)

    # Time to explore and map the paths, while there are still discovered nodes to check, we shall continue.
    while discovered:

        # We grab the node with lowest F from all discovered nodes.
        current_best_node = min(discovered, key=lambda o: o.f)

        # If that that node is the end node...
        if current_best_node == end_node:

            # Save f for later.
            f = current_best_node.f

            # Reconstruct the path.
            while current_best_node:
                current_slot = current_best_node.slot

                # We assigna a value to the path slot, so we can draw colors over it.
                path[current_slot.getFila()][current_slot.getCol()] = (
                    0, current_best_node.number)

                # If theres no more nodes to reconstruct, we are finished! :D
                if not current_best_node.parent:
                    return f
                else:
                    current_best_node = current_best_node.parent

        # We assigna a value to the checked slot, so we can draw colors over it.
        path[current_best_node.slot.getFila()][current_best_node.slot.getCol()] = (
            1, current_best_node.number)

        # We checked the node with lowest F, sadly that wasnt the end node, so we move it to the checked set.
        discovered.remove(current_best_node)
        checked.add(current_best_node)

        # We check the neighboring nodes. For each neighbor coordinate..
        for neighbor_slot in neighborSlots(current_best_node):

            # Check if the current neighbor coordinate is actually in bounds of the map.
            if not map.inBounds(neighbor_slot.getFila(), neighbor_slot.getCol()):
                continue

            # We make sure that the neighbor coordinate is not a wall
            if map.getCelda(neighbor_slot.getFila(), neighbor_slot.getCol()) != 0:
                continue

            # Create a new node with the neighbor coordinates, and also attach the parent node (current best node) to it.
            neighbor_node = Node(current_best_node, neighbor_slot)

            # Check if the current neighbor node wasn't checked on previous iterations.
            if neighbor_node in checked:
                continue

            # If the node has not been discovered, we calculate its values and add it to discovered
            if neighbor_node not in discovered:

                neighbor_node.g = current_best_node.g + \
                    movementCost(current_best_node, neighbor_node)
                neighbor_node.h = heuristic(
                    neighbor_node.slot, end_node.slot)

                neighbor_node.f = neighbor_node.g + neighbor_node.h
                neighbor_node.number = current_best_node.number + 1

                discovered.add(neighbor_node)
                continue

            # If we have already discovered the neighboring Node and the current best node has better values than the neighboring node's parent ...
            for node_discovered in discovered:
                if node_discovered == neighbor_node and node_discovered.g > current_best_node.g + movementCost(node_discovered, current_best_node):

                    # We update g and the parent of the neighboring node! (A better path has been found to reach the neighboring Node.)
                    node_discovered.g = current_best_node.g + \
                        movementCost(node_discovered, current_best_node)

                    node_discovered.parent = current_best_node
                    node_discovered.number = current_best_node.number + 1

                break

    return -1


# Returns an array with the neighboring coordinates of the current coordinates.
def neighborSlots(Node):
    """Get neighboring slots of the Node"""
    casilla = Node.slot
    # ↑ = ( 0, 1 )
    # ↓ = ( 0, -1)
    # → = (-1, 0 )
    # ← = ( 1, 0 )
    # ↗ = ( 1, 1 )
    # ↘ = ( 1, -1)
    # ↖ = (-1, 1 )
    # ↙ = (-1, -1)
    return [casilla + Casilla(0, 1), casilla + Casilla(0, -1), casilla + Casilla(1, 0), casilla + Casilla(-1, 0),
            casilla + Casilla(1, 1), casilla + Casilla(1, -1), casilla + Casilla(-1, 1), casilla + Casilla(-1, -1)]


# Returns the cost of movement, from node1 (n1) to node2 (n2)
def movementCost(n1, n2):
    """Get the movement cost from n1 to n2 (both must be neighbors)"""
    diagonal_movements = set({Casilla(1, 1), Casilla(1, -1),
                              Casilla(-1, -1), Casilla(-1, 1)})

    if ((n1.slot - n2.slot) in diagonal_movements):
        return 1.5

    return 1
