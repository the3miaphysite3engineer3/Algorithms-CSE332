import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import random
from collections import defaultdict
import time

# Define colors for visualization
COLORS = ['#FF5733', '#33FF57', '#3357FF']  # Red, Green, Blue

class Board:
    def __init__(self, n, missing_x=None, missing_y=None):
        """Initialize a 2^n x 2^n board with a missing square."""
        self.size = 2**n
        self.board = np.zeros((self.size, self.size), dtype=int)
        
        # If missing coordinates not provided, place in random position
        if missing_x is None or missing_y is None:
            missing_x = random.randint(0, self.size - 1)
            missing_y = random.randint(0, self.size - 1)
        
        # Mark missing square with -1
        self.board[missing_y, missing_x] = -1
        self.tromino_count = 0
        self.color_board = np.zeros((self.size, self.size), dtype=int)
    
    def visualize(self, title="L-Tromino Tiling", ax=None):
        """Visualize the board with colored trominoes."""
        if ax is None:
            fig, ax = plt.subplots(figsize=(10, 10))
        
        for i in range(self.size):
            for j in range(self.size):
                color = 'black'
                if self.board[i, j] == -1:
                    color = 'black'
                elif self.board[i, j] > 0:
                    color_idx = self.color_board[i, j] - 1
                    color = COLORS[color_idx % len(COLORS)]
                
                rect = patches.Rectangle(
                    (j, self.size - i - 1), 1, 1,
                    linewidth=1, edgecolor='black',
                    facecolor=color
                )
                ax.add_patch(rect)
        
        ax.set_xlim(0, self.size)
        ax.set_ylim(0, self.size)
        ax.set_title(title)
        ax.set_aspect('equal')
        ax.axis('off')  # Remove axes

    
    def place_tromino(self, x, y, missing_x, missing_y, size, algorithm_name):
        """Place a tromino on the board based on the missing square position."""
        if size == 2:
            # Base case: place a single tromino in a 2x2 board
            self.tromino_count += 1
            for i in range(y, y + 2):
                for j in range(x, x + 2):
                    if i != missing_y or j != missing_x:
                        self.board[i, j] = self.tromino_count
            return
        
        # Find the quadrant of the missing square
        half = size // 2
        center_x, center_y = x + half - 1, y + half - 1  # Center coordinates
        
        # Determine which quadrant contains the missing square
        quad_x = 1 if missing_x > center_x else 0
        quad_y = 1 if missing_y > center_y else 0
        
        # Place the central tromino
        self.tromino_count += 1
        central_tromino_id = self.tromino_count
        
        # Place tromino in the center, covering one square in each quadrant except the one with the missing square
        for i in range(2):
            for j in range(2):
                if i != quad_y or j != quad_x:
                    new_y = center_y + i
                    new_x = center_x + j
                    self.board[new_y, new_x] = central_tromino_id
        
        # Recursively tile each quadrant
        # Upper left quadrant
        new_missing_y = center_y if quad_y == 0 and quad_x == 0 else center_y
        new_missing_x = center_x if quad_y == 0 and quad_x == 0 else center_x
        if quad_y == 0 and quad_x == 0:
            new_missing_y, new_missing_x = missing_y, missing_x
        self.place_tromino(x, y, new_missing_x, new_missing_y, half, algorithm_name)
        
        # Upper right quadrant
        new_missing_y = center_y if quad_y == 0 and quad_x == 1 else center_y
        new_missing_x = center_x + 1 if quad_y == 0 and quad_x == 1 else center_x + 1
        if quad_y == 0 and quad_x == 1:
            new_missing_y, new_missing_x = missing_y, missing_x
        self.place_tromino(x + half, y, new_missing_x, new_missing_y, half, algorithm_name)
        
        # Lower left quadrant
        new_missing_y = center_y + 1 if quad_y == 1 and quad_x == 0 else center_y + 1
        new_missing_x = center_x if quad_y == 1 and quad_x == 0 else center_x
        if quad_y == 1 and quad_x == 0:
            new_missing_y, new_missing_x = missing_y, missing_x
        self.place_tromino(x, y + half, new_missing_x, new_missing_y, half, algorithm_name)
        
        # Lower right quadrant
        new_missing_y = center_y + 1 if quad_y == 1 and quad_x == 1 else center_y + 1
        new_missing_x = center_x + 1 if quad_y == 1 and quad_x == 1 else center_x + 1
        if quad_y == 1 and quad_x == 1:
            new_missing_y, new_missing_x = missing_y, missing_x
        self.place_tromino(x + half, y + half, new_missing_x, new_missing_y, half, algorithm_name)


# 1. Divide and Conquer with Color Assignment
class DivideAndConquerAlgorithm:
    def __init__(self, n, missing_x=None, missing_y=None):
        self.board = Board(n, missing_x, missing_y)
    
    def run(self):
        size = self.board.size
        # Find missing square position
        missing_y, missing_x = np.where(self.board.board == -1)
        missing_y, missing_x = missing_y[0], missing_x[0]
        
        # Place trominoes using divide and conquer
        self.board.place_tromino(0, 0, missing_x, missing_y, size, "Divide and Conquer")
        
        # Assign colors (3-coloring)
        self.assign_colors()
        
        return self.board
    
    def assign_colors(self):
        """Assign colors to trominoes such that no adjacent trominoes have the same color."""
        # Create a graph where nodes are tromino IDs and edges are adjacency relationships
        adjacency = defaultdict(set)
        
        # Find adjacencies
        for i in range(self.board.size):
            for j in range(self.board.size - 1):
                id1 = self.board.board[i, j]
                id2 = self.board.board[i, j+1]
                if id1 > 0 and id2 > 0 and id1 != id2:
                    adjacency[id1].add(id2)
                    adjacency[id2].add(id1)
        
        for i in range(self.board.size - 1):
            for j in range(self.board.size):
                id1 = self.board.board[i, j]
                id2 = self.board.board[i+1, j]
                if id1 > 0 and id2 > 0 and id1 != id2:
                    adjacency[id1].add(id2)
                    adjacency[id2].add(id1)
        
        # Assign colors using greedy algorithm
        colors = {}
        for tromino_id in range(1, self.board.tromino_count + 1):
            used_colors = {colors.get(adj) for adj in adjacency[tromino_id] if adj in colors}
            
            # Find the first available color
            for color in range(1, 4):  # We only need 3 colors
                if color not in used_colors:
                    colors[tromino_id] = color
                    break
        
        # Apply colors to the board
        for i in range(self.board.size):
            for j in range(self.board.size):
                if self.board.board[i, j] > 0:
                    self.board.color_board[i, j] = colors[self.board.board[i, j]]


# 2. Graph Coloring with Constraint Propagation
class GraphColoringAlgorithm:
    def __init__(self, n, missing_x=None, missing_y=None):
        self.board = Board(n, missing_x, missing_y)
    
    def run(self):
        size = self.board.size
        # Find missing square position
        missing_y, missing_x = np.where(self.board.board == -1)
        missing_y, missing_x = missing_y[0], missing_x[0]
        
        # Place trominoes using divide and conquer
        self.board.place_tromino(0, 0, missing_x, missing_y, size, "Graph Coloring")
        
        # Build the constraint graph
        self.adjacency_graph = self.build_adjacency_graph()
        
        # Solve the CSP
        self.colors = {}
        self.solve_csp(1)
        
        # Apply colors to the board
        for i in range(self.board.size):
            for j in range(self.board.size):
                if self.board.board[i, j] > 0:
                    self.board.color_board[i, j] = self.colors[self.board.board[i, j]]
        
        return self.board
    
    def build_adjacency_graph(self):
        """Build a graph where nodes are tromino IDs and edges connect adjacent trominoes."""
        adjacency = defaultdict(set)
        
        # Find adjacencies horizontally
        for i in range(self.board.size):
            for j in range(self.board.size - 1):
                id1 = self.board.board[i, j]
                id2 = self.board.board[i, j+1]
                if id1 > 0 and id2 > 0 and id1 != id2:
                    adjacency[id1].add(id2)
                    adjacency[id2].add(id1)
        
        # Find adjacencies vertically
        for i in range(self.board.size - 1):
            for j in range(self.board.size):
                id1 = self.board.board[i, j]
                id2 = self.board.board[i+1, j]
                if id1 > 0 and id2 > 0 and id1 != id2:
                    adjacency[id1].add(id2)
                    adjacency[id2].add(id1)
        
        return adjacency
    
    def solve_csp(self, tromino_id):
        """Backtracking CSP solver for the 3-coloring problem."""
        if tromino_id > self.board.tromino_count:
            return True
        
        for color in range(1, 4):  # Try each color (1, 2, 3)
            if self.is_valid_color(tromino_id, color):
                self.colors[tromino_id] = color
                if self.solve_csp(tromino_id + 1):
                    return True
                del self.colors[tromino_id]  # Backtrack
        
        return False
    
    def is_valid_color(self, tromino_id, color):
        """Check if assigning color to tromino_id is consistent with current assignments."""
        for adj in self.adjacency_graph[tromino_id]:
            if adj in self.colors and self.colors[adj] == color:
                return False
        return True



# 3. SAT Solver Approach (Simplified)
class SATSolverAlgorithm:
    """
    Note: A full SAT solver implementation is beyond the scope of this code.
    This is a simplified version that uses the divide and conquer for placement
    and then models the coloring problem as a constraint satisfaction problem.
    """
    def __init__(self, n, missing_x=None, missing_y=None):
        self.board = Board(n, missing_x, missing_y)
    
    def run(self):
        size = self.board.size
        # Find missing square position
        missing_y, missing_x = np.where(self.board.board == -1)
        missing_y, missing_x = missing_y[0], missing_x[0]
        
        # Place trominoes using divide and conquer
        self.board.place_tromino(0, 0, missing_x, missing_y, size, "SAT Solver Approach")
        
        # Since a full SAT solver is complex, we'll use backtracking to assign colors
        # This simulates the SAT model being solved
        adjacency = self.build_adjacency_graph()
        colors = {}
        self.solve_sat_model(adjacency, colors, 1)
        
        # Apply the colors to the board
        for i in range(self.board.size):
            for j in range(self.board.size):
                if self.board.board[i, j] > 0:
                    self.board.color_board[i, j] = colors[self.board.board[i, j]]
        
        return self.board
    
    def build_adjacency_graph(self):
        """Build adjacency graph from the board."""
        adjacency = defaultdict(set)
        
        # Find adjacencies horizontally
        for i in range(self.board.size):
            for j in range(self.board.size - 1):
                id1 = self.board.board[i, j]
                id2 = self.board.board[i, j+1]
                if id1 > 0 and id2 > 0 and id1 != id2:
                    adjacency[id1].add(id2)
                    adjacency[id2].add(id1)
        
        # Find adjacencies vertically
        for i in range(self.board.size - 1):
            for j in range(self.board.size):
                id1 = self.board.board[i, j]
                id2 = self.board.board[i+1, j]
                if id1 > 0 and id2 > 0 and id1 != id2:
                    adjacency[id1].add(id2)
                    adjacency[id2].add(id1)
        
        return adjacency
    
    def solve_sat_model(self, adjacency, colors, tromino_id):
        """Solve the coloring problem using backtracking (simulating SAT solving)."""
        if tromino_id > self.board.tromino_count:
            return True
        
        for color in range(1, 4):  # Try each color (1, 2, 3)
            if self.is_valid_color(adjacency, colors, tromino_id, color):
                colors[tromino_id] = color
                if self.solve_sat_model(adjacency, colors, tromino_id + 1):
                    return True
                del colors[tromino_id]  # Backtrack
        
        return False
    
    def is_valid_color(self, adjacency, colors, tromino_id, color):
        """Check if assigning color to tromino_id is consistent with current assignments."""
        for adj in adjacency[tromino_id]:
            if adj in colors and colors[adj] == color:
                return False
        return True


# Run all algorithms and display results
def run_all_algorithms(n=3, missing_x=0, missing_y=0):
    """Run all algorithms and display their results in a single subplot view."""
    algorithms = [
        ("Divide and Conquer", DivideAndConquerAlgorithm(n, missing_x, missing_y)),
        ("Graph Coloring + CSP", GraphColoringAlgorithm(n, missing_x, missing_y)),
        ("SAT Solver Approach", SATSolverAlgorithm(n, missing_x, missing_y))
    ]
    
    results = []
    for name, algorithm in algorithms:
        print(f"Running {name}...")
        start_time = time.time()
        board = algorithm.run()
        end_time = time.time()
        results.append((name, board, end_time - start_time))
    
    # Plot results side by side
    fig, axs = plt.subplots(1, len(results), figsize=(6 * len(results), 6))
    if len(results) == 1:
        axs = [axs]
    
    for ax, (name, board, exec_time) in zip(axs, results):
        board.visualize(f"{name}\nTime: {exec_time:.4f}s", ax=ax)
    
    plt.tight_layout()
    plt.show()


# Run the demonstration with a 4x4 board (n=2)
if __name__ == "__main__":
    # You can adjust these parameters as needed
    run_all_algorithms(n=4, missing_x=0, missing_y=0)  # Creates a 2^3 = 8x8 board
