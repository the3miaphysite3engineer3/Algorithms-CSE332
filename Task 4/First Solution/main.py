import heapq
from collections import deque

# Board dimensions and knight moves
ROWS, COLS = 4, 3
KNIGHT_MOVES = [(-2, -1), (-2, 1), (-1, -2), (-1, 2),
                (1, -2), (1, 2), (2, -1), (2, 1)]

# Precompute minimal knight moves from any cell (r,c) to any target row (0 for white, 2 for black)
# This is used as an admissible heuristic.
knight_distance_table = {}

def compute_knight_distances():
    for r in range(ROWS):
        for c in range(COLS):
            for target_row in [0, 2]:
                # BFS from (r, c) until any cell in target_row is reached.
                visited = set()
                q = deque([(r, c, 0)])
                found = None
                while q:
                    cr, cc, d = q.popleft()
                    if cr == target_row:
                        found = d
                        break
                    for dr, dc in KNIGHT_MOVES:
                        nr, nc = cr + dr, cc + dc
                        if 0 <= nr < ROWS and 0 <= nc < COLS and (nr, nc) not in visited:
                            visited.add((nr, nc))
                            q.append((nr, nc, d + 1))
                knight_distance_table[(r, c, target_row)] = found if found is not None else 999

compute_knight_distances()

class Board:
    def __init__(self, positions, moves=None):
        """
        positions: dict mapping (row, col) -> 'W', 'B', or None.
        moves: list of moves taken to reach this state.
        """
        self.positions = positions
        self.moves = moves if moves is not None else []
        self.h = self.calculate_heuristic()
        self.g = len(self.moves)
        self.f = self.g + self.h

    def calculate_heuristic(self):
        """Sum of minimum knight moves for each knight to reach its target row.
           White knights should reach row 0; black knights row 2."""
        total = 0
        for (r, c), piece in self.positions.items():
            if piece == 'W':
                total += knight_distance_table[(r, c, 0)]
            elif piece == 'B':
                total += knight_distance_table[(r, c, 2)]
        return total

    def generate_moves(self):
        """Generate all legal moves as tuples: ((from_row, from_col), (to_row, to_col))."""
        moves = []
        for (r, c), piece in self.positions.items():
            if piece is None:
                continue
            for dr, dc in KNIGHT_MOVES:
                nr, nc = r + dr, c + dc
                if 0 <= nr < ROWS and 0 <= nc < COLS:
                    if self.positions.get((nr, nc)) is None:
                        moves.append(((r, c), (nr, nc)))
        return moves

    def move(self, move):
        """Return a new Board after applying the given move."""
        old_pos, new_pos = move
        new_positions = self.positions.copy()
        new_positions[new_pos] = new_positions[old_pos]
        new_positions[old_pos] = None
        new_moves = self.moves + [move]
        return Board(new_positions, new_moves)

    def is_goal(self):
        """Goal: all white knights in row 0 and all black knights in row 2."""
        for (r, c), piece in self.positions.items():
            if piece == 'W' and r != 0:
                return False
            if piece == 'B' and r != 3:
                return False
        return True

    def state_key(self):
        """A hashable representation of the board state."""
        return tuple(sorted(self.positions.items()))

    def display(self):
        """Prints the board. 'W' for white, 'B' for black, '.' for empty."""
        for r in range(ROWS):
            line = []
            for c in range(COLS):
                cell = self.positions.get((r, c))
                line.append(cell if cell in ('W', 'B') else '.')
            print(' '.join(line))
        print()

def solve_knights_astar():
    # Initial positions for the 3x4 board:
    # Black knights in row 0; white knights in row 2.
    initial_positions = {
        (0, 0): 'B', (0, 1): 'B', (0, 2): 'B',
        (1, 0): None, (1, 1): None, (1, 2): None,
        (2, 0): None, (2, 1): None, (2, 2): None,
        (3, 0): 'W', (3, 1): 'W', (3, 2): 'W',
    }
    start = Board(initial_positions)
    open_list = []
    counter = 0  # Tiebreaker counter for heap
    heapq.heappush(open_list, (start.f, counter, start))
    closed = set()

    while open_list:
        _, _, current = heapq.heappop(open_list)
        if current.is_goal():
            return current  # Found optimal solution.
        state_key = current.state_key()
        if state_key in closed:
            continue
        closed.add(state_key)
        for move in current.generate_moves():
            neighbor = current.move(move)
            neighbor_key = neighbor.state_key()
            if neighbor_key not in closed:
                counter += 1
                heapq.heappush(open_list, (neighbor.f, counter, neighbor))
    return None

def main():
    solution = solve_knights_astar()
    if solution:
        print("Optimal solution found in {} moves.\n".format(len(solution.moves)))
        # Display the sequence of moves with board states.
        # Reconstruct the board step by step.
        initial_positions = {
            (0, 0): 'B', (0, 1): 'B', (0, 2): 'B',
            (1, 0): None, (1, 1): None, (1, 2): None,
            (2, 0): None, (2, 1): None, (2, 2): None,
            (3, 0): 'W', (3, 1): 'W', (3, 2): 'W',
        }
        current = Board(initial_positions)
        print("Initial Board:")
        current.display()
        move_count = 0
        for move in solution.moves:
            move_count += 1
            print("Move {}: {} -> {}".format(move_count, move[0], move[1]))
            current = current.move(move)
            current.display()
    else:
        print("No solution found.")

if __name__ == "__main__":
    main()