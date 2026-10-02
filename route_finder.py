import sys

# The undirected graph connections between Makerere University schools and landmarks[cite: 1, 2].
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

# Build adjacency list graph
GRAPH = {}
VALID_PLACES = set()

for u, v in EDGES:
    VALID_PLACES.add(u)
    VALID_PLACES.add(v)
    if u not in GRAPH: GRAPH[u] = []
    if v not in GRAPH: GRAPH[v] = []
    GRAPH[u].append(v)
    GRAPH[v].append(u)

# Create a case-insensitive map for strict input matching requirements.
PLACES_MAP = {place.lower(): place for place in VALID_PLACES}


class Node:
    """A search node containing the required fields for the search tree."""

    def __init__(self, state, parent=None, action=None, path_cost=0):
        self.state = state  # STATE
        self.parent = parent  # PARENT
        self.action = action  # ACTION
        self.path_cost = path_cost  # PATH-COST


def solution(node):
    """Traces parent pointers back to the root to assemble the ordered list of places."""
    route = []
    while node:
        route.append(node.state)
        node = node.parent
    return route[::-1]


def search(source, destination, algorithm, use_reached=True):
    """
    Generic search loop implementing BFS (queue/FIFO) and DFS (stack/LIFO)[cite: 3].
    """
    initial_node = Node(state=source, path_cost=0)
    frontier = [initial_node]

    # Reached table mapping the state directly to the node[cite: 3].
    reached = {source: initial_node} if use_reached else {}
    nodes_expanded = 0

    while frontier:
        # Safety cap applied to terminate infinite loops during tree-like search evaluation[cite: 3].
        if nodes_expanded >= 10000:
            return None, nodes_expanded

        # Strategy selection for node removal from the frontier[cite: 3].
        if algorithm == 'BFS':
            node = frontier.pop(0)  # Removes from the front for BFS queue[cite: 3].
        else:
            node = frontier.pop()  # Removes from the back for DFS stack[cite: 3].

        # The goal test must be applied when the node is extracted from the frontier[cite: 3].
        if node.state.lower() == destination.lower():
            return solution(node), nodes_expanded

        # Count tracks nodes that fail the goal test and have their children generated[cite: 3].
        nodes_expanded += 1

        # Ensures deterministic execution by evaluating neighbors alphabetically[cite: 3].
        neighbors = sorted(GRAPH.get(node.state, []))

        # Pushing onto the LIFO stack in reverse alphabetical order ensures DFS explores the first alphabetical neighbor initially[cite: 3].
        if algorithm == 'DFS':
            neighbors.reverse()

        for neighbor in neighbors:
            # Each direct connection hop strictly costs 1[cite: 1, 6].
            child = Node(
                state=neighbor,
                parent=node,
                action=neighbor,
                path_cost=node.path_cost + 1
            )

            if use_reached:
                if child.state not in reached or child.path_cost < reached[child.state].path_cost:
                    reached[child.state] = child
                    frontier.append(child)
            else:
                frontier.append(child)

    return None, nodes_expanded


import string
import sys


# [Insert previous EDGES, GRAPH, VALID_PLACES, Node class, solution(), and search() here]

def main():
    print("Makerere Campus Route Finder")
    print("----------------------------")

    # Sort places alphabetically and map them to uppercase letters (A, B, C, etc.)
    sorted_places = sorted(VALID_PLACES)
    letters = string.ascii_uppercase
    place_menu = {letters[i]: place for i, place in enumerate(sorted_places)}

    # Display the menu of places
    print("\nAvailable Places:")
    for letter, place in place_menu.items():
        print(f"[{letter}] {place}")

    try:
        # Prompt user to select letters instead of typing full names to prevent input errors.
        source_letter = input("\nEnter the letter for the source: ").strip().upper()
        if source_letter not in place_menu:
            # Prevents crashes on unknown input and exits cleanly[cite: 4].
            print("Error: Invalid selection. Please restart and choose a valid letter.")
            return
        source = place_menu[source_letter]

        dest_letter = input("Enter the letter for the destination: ").strip().upper()
        if dest_letter not in place_menu:
            print("Error: Invalid selection. Please restart and choose a valid letter.")
            return
        destination = place_menu[dest_letter]

        # Menu for algorithm selection
        print("\nAvailable Algorithms:")
        print("[A] BFS")
        print("[B] DFS")
        algo_letter = input("Select search algorithm (A or B): ").strip().upper()

        if algo_letter == 'A':
            algo_name = 'BFS'
        elif algo_letter == 'B':
            algo_name = 'DFS'
        else:
            print("Error: Invalid algorithm selection. Please choose A or B[cite: 4].")
            return

        # Switch for the reached table (B4 requirement)[cite: 3].
        use_reached_input = input("\nUse reached table for graph search? (Y/N): ").strip().upper()
        use_reached = use_reached_input != 'N'

        # If source equals destination, output a 1-place route with cost 0[cite: 4].
        if source == destination:
            route = [source]
            cost = 0
            expanded = 0
        else:
            route, expanded = search(source, destination, algo_name, use_reached)
            cost = len(route) - 1 if route else 0

        if route is None:
            # Required output when the search exhausts the frontier without a solution[cite: 4].
            print("\nNo route found.")
        else:
            # Output format matched exactly to the assignment specification[cite: 4].
            print(f"\nAlgorithm: {algo_name}")
            print(f"Route: {' -> '.join(route)}")
            print(f"Cost (hops): {cost}")
            print(f"Nodes expanded: {expanded}")

            if expanded >= 10000:
                print("\nWarning: Terminated at 10,000 expansions to prevent infinite loops[cite: 3].")

    except (EOFError, KeyboardInterrupt):
        print("\nExiting.")
        sys.exit(0)


if __name__ == "__main__":
    main()