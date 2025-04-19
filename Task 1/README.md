# Tromino Tiling Algorithm Report

## Overview
We are given a 2n × 2n board with one missing square. Our task is to tile this board with right trominoes of three different colors, such that no pair of trominoes that share an edge have the same color. The right tromino is an L-shaped tile formed by three adjacent squares.

## Algorithm: Divide and Conquer
The tromino tiling problem is solved recursively:
- The board is divided into four quadrants.
- The quadrant containing the missing square is identified.
- A central tromino is placed to cover the center of the board, avoiding the quadrant with the missing square.
- The process recurses on each quadrant, treating the central tromino's squares as new "missing" squares for the other quadrants.
- The base case is a 2x2 board, where a single tromino fills the three non-missing squares.

## Pseudocode
```pseudo
function tromino_tile(x, y, size, missing_x, missing_y):
    if size == 2:
        Place a tromino on the 2x2 board, skipping (missing_x, missing_y)
        Assign a color not used by adjacent trominoes
        return
    mid = size // 2
    Determine which quadrant contains (missing_x, missing_y)
    Place a central tromino to cover the center, avoiding the quadrant with the missing square
    For each quadrant:
        if quadrant contains the missing square:
            recurse with that missing square
        else:
            recurse with the square covered by the central tromino as the missing square

function choose_color(cells):
    Find colors of adjacent trominoes
    Return a color not used by neighbors
```
## Code Structure
### TrominoTiler Class
- **Initialization**: Sets up the board, missing square, and data structures for tracking trominoes and their colors.
- **tile()**: Public method to start the tiling process.
- **_tile()**: Recursive helper that implements the divide and conquer logic.
- **_choose_color()**: Assigns a color to each tromino, ensuring no adjacent trominoes share the same color.
- **plot()**: Visualizes the board and trominoes using matplotlib.

### Coloring Logic
- Three distinct colors are used for trominoes.
- When placing a tromino, the algorithm checks the colors of adjacent trominoes and selects a color not used by neighbors.
- This ensures that no two adjacent trominoes share the same color, which is important for clear visualization and can be extended for coloring constraints.

### Visualization
- The `plot()` method uses matplotlib to draw each tromino as a colored region on the board.
- The missing square is highlighted with a white color and a hatch pattern.
- Grid lines and axis ticks are added for clarity.

## Usage Example
```python
from tromino_tiling import TrominoTiler

tiler = TrominoTiler(n=3, missing=(2, 3))
tiler.tile()
tiler.plot()
```

## Conclusion
This implementation provides a clear, visual, and well-documented solution to the tromino tiling problem. The code is modular and can be easily extended or adapted for related tiling and coloring problems.

## Big O Analysis
The tromino tiling algorithm operates on a 2^n × 2^n board. At each recursive step, the board is divided into four quadrants, and the algorithm recurses on each quadrant. The work done at each level (placing a central tromino and determining colors) is O(1) per quadrant, but there are four recursive calls for each division. The recurrence relation is:

T(N) = 4T(N/2) + O(1)

where N is the side length of the board. Solving this recurrence gives T(N) = O(N^2), which matches the total number of cells on the board. Thus, the time complexity is O(N^2), where N = 2^n.

Space complexity is also O(N^2), as the algorithm stores the board and the list of placed trominoes. The recursion stack depth is O(log N), but this is dominated by the board storage.
