"""
Makerere Campus Route Finder (CSC 2114 Practical 3)
BFS and DFS share ONE generic search loop; they differ only in which end of
the frontier a node is removed from. Every hop costs 1.

Source and destination must be schools; landmarks are walk-through only.

Usage:
    python route_finder.py              # interactive prompts
    python route_finder.py --no-reached # tree-like search (reached table off)
"""
import sys
from collections import deque

EDGES = [
    ("Main Building", "Freedom Square"), ("Main Building", "Main Library"),
    ("Main Building", "School of Social Sciences"),
    ("Main Building", "School of Liberal and Performing Arts"),
    ("Freedom Square", "Main Library"), ("Freedom Square", "School of Law"),
    ("Freedom Square", "Central Teaching Facility"),
    ("Main Library", "School of Education"), ("Main Library", "School of Economics"),
    ("Central Teaching Facility", "CoCIS"),
    ("Central Teaching Facility", "School of Statistics and Planning"),
    ("CoCIS", "School of Statistics and Planning"), ("CoCIS", "School of Engineering"),
    ("School of Engineering", "School of the Built Environment"),
    ("School of Engineering", "Margaret Trowell School of Industrial and Fine Art"),
    ("School of the Built Environment", "Margaret Trowell School of Industrial and Fine Art"),
    ("Margaret Trowell School of Industrial and Fine Art", "School of Liberal and Performing Arts"),
    ("School of Education", "School of Social Sciences"),
    ("School of Education", "College of Natural Sciences"),
    ("College of Natural Sciences", "School of Food Technology, Nutrition and Bioengineering"),
    ("School of Food Technology, Nutrition and Bioengineering", "School of Agricultural Sciences"),
    ("School of Agricultural Sciences", "School of Veterinary Medicine"),
    ("School of Statistics and Planning", "School of Economics"),
    ("School of Economics", "School of Law"),
]

# Adjacency list (undirected: each edge is stored in both directions).
GRAPH = {}
for _u, _v in EDGES:
    GRAPH.setdefault(_u, []).append(_v)
    GRAPH.setdefault(_v, []).append(_u)

# Landmarks can be walked through but are not schools, so they are never
# valid sources or destinations. Only the 14 schools can be chosen.
LANDMARKS = {"Main Building", "Freedom Square", "Main Library",
             "Central Teaching Facility"}
SCHOOLS = sorted(name for name in GRAPH if name not in LANDMARKS)

# Lower-cased school name -> official name, for case-insensitive matching.
PLACES = {name.lower(): name for name in SCHOOLS}

EXPANSION_CAP = 10_000


class Node:
    """Search-tree node with the four lecture fields."""

    def __init__(self, state, parent=None, action=None, path_cost=0):
        self.state = state          # STATE
        self.parent = parent        # PARENT
        self.action = action        # ACTION (the place we walked to)
        self.path_cost = path_cost  # PATH-COST (hops so far)


def solution(node):
    """Follow PARENT pointers back to the root; return places in order."""
    route = []
    while node is not None:
        route.append(node.state)
        node = node.parent
    return route[::-1]


def search(source, destination, algorithm, use_reached=True):
    """
    Generic search. Returns (route or None, nodes_expanded, hit_cap).
    BFS: frontier is a queue, remove from the front.
    DFS: frontier is a stack, remove from the back.
    use_reached=False gives tree-like search (stopped by EXPANSION_CAP).
    """
    root = Node(source)
    frontier = deque([root])
    reached = {source: root} if use_reached else None
    expanded = 0

    while frontier:
        # The ONLY difference between the two algorithms:
        node = frontier.popleft() if algorithm == "BFS" else frontier.pop()

        # Goal test when the node is removed from the frontier.
        if node.state == destination:
            return solution(node), expanded, False

        # Safety cap, checked before expanding another node.
        if expanded >= EXPANSION_CAP:
            return None, expanded, True
        expanded += 1

        # Alphabetical order. A stack pops the last item pushed, so DFS pushes
        # in reverse so the alphabetically first neighbour is explored first.
        neighbours = sorted(GRAPH[node.state])
        if algorithm == "DFS":
            neighbours.reverse()

        for place in neighbours:
            if use_reached and place in reached:
                continue  # repeated state: skip it
            child = Node(place, node, place, node.path_cost + 1)
            if use_reached:
                reached[place] = child
            frontier.append(child)

    return None, expanded, False


def find_place(text):
    """Match a place name ignoring case and surrounding spaces."""
    return PLACES.get(text.strip().lower())


def show_places():
    print("Valid places (schools):")
    for name in SCHOOLS:
        print(f"  - {name}")


def ask_place(prompt):
    text = input(prompt)
    place = find_place(text)
    if place is None:
        print(f'\nUnknown place: "{text.strip()}".')
        show_places()
    return place


def main():
    use_reached = "--no-reached" not in sys.argv[1:]
    print("Makerere Campus Route Finder")
    print("----------------------------")
    show_places()
    print()

    try:
        source = ask_place("Source: ")
        if source is None:
            return
        destination = ask_place("Destination: ")
        if destination is None:
            return

        algorithm = input("Algorithm (BFS or DFS): ").strip().upper()
        if algorithm not in ("BFS", "DFS"):
            print(f'\nUnknown algorithm: "{algorithm}". Valid algorithms: BFS, DFS.')
            return
    except (EOFError, KeyboardInterrupt):
        print("\nExiting.")
        return

    route, expanded, hit_cap = search(source, destination, algorithm, use_reached)

    if hit_cap:
        print(f"\nWarning: stopped at the {EXPANSION_CAP:,}-expansion cap "
              f"(reached table {'on' if use_reached else 'off'}).")
    if route is None:
        print("No route found.")
        return

    print(f"\nAlgorithm: {algorithm}")
    print(f"Route: {' -> '.join(route)}")
    print(f"Cost (hops): {len(route) - 1}")
    print(f"Nodes expanded: {expanded}")


if __name__ == "__main__":
    main()