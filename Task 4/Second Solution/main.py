class Board:
    def __init__(self, positions):
        self.positions = positions  # {(row, col): 'W'/'B'/None}
        self.heuristic = self.calculate_heuristic()

    def calculate_heuristic(self):
        total = 0
        for (row, col), color in self.positions.items():
            if color == 'W':
                total += row  # White knights target row 0 (top)
            elif color == 'B':
                total += (3 - row)  # Black knights target row 3 (bottom)
        return total

    def generate_moves(self):
        moves = []
        for (r, c), color in self.positions.items():
            if color is None:
                continue
            deltas = [(-2, -1), (-2, 1), (-1, -2), (-1, 2),
                      (1, -2), (1, 2), (2, -1), (2, 1)]
            for dr, dc in deltas:
                nr, nc = r + dr, c + dc
                if 0 <= nr < 4 and 0 <= nc < 3:  # 4x3 boundaries
                    if self.positions.get((nr, nc)) is None:
                        old_dist = r if color == 'W' else (3 - r)
                        new_dist = nr if color == 'W' else (3 - nr)
                        delta = new_dist - old_dist
                        moves.append((delta, -old_dist, (r, c), (nr, nc)))
        return moves

    def display(self):
        """Prints the 4x3 board."""
        for row in range(4):
            line = []
            for col in range(3):
                cell = self.positions.get((row, col))
                line.append(cell if cell in ('W', 'B') else '.')
            print(' '.join(line))
        print()

def solve_knights():
    # Initial positions for 4x3 board
    initial_positions = {
        (0, 0): 'B', (0, 1): 'B', (0, 2): 'B',
        (1, 0): None, (1, 1): None, (1, 2): None,
        (2, 0): None, (2, 1): None, (2, 2): None,
        (3, 0): 'W', (3, 1): 'W', (3, 2): 'W',
    }
    current_board = Board(initial_positions)
    move_sequence = []
    visited = set()

    print("Initial Board:")
    current_board.display()

    while current_board.heuristic > 0:
        moves = current_board.generate_moves()
        if not moves:
            print("No valid moves left. Stuck!")
            return []

        # Prioritize moves that reduce the heuristic the most
        moves.sort(key=lambda x: (x[0], x[1]))

        best_move = None
        for move in moves:
            delta, _, old_pos, new_pos = move
            new_positions = current_board.positions.copy()
            new_positions[old_pos] = None
            new_positions[new_pos] = current_board.positions[old_pos]
            state_key = tuple(sorted(new_positions.items()))
            if state_key not in visited:
                best_move = move
                visited.add(state_key)
                break

        if not best_move:
            print("All moves lead to visited states. Stuck!")
            return []

        # Apply the move
        delta, _, old_pos, new_pos = best_move
        move_sequence.append((old_pos, new_pos))
        new_positions = current_board.positions.copy()
        new_positions[old_pos] = None
        new_positions[new_pos] = current_board.positions[old_pos]
        current_board = Board(new_positions)

        print(f"Move {len(move_sequence)}: {old_pos} -> {new_pos}")
        current_board.display()

    return move_sequence

moves = solve_knights()
print(f"Total moves: {len(moves)}")