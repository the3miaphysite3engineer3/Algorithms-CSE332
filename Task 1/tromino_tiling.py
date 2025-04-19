import matplotlib.pyplot as plt
import numpy as np

# Define three distinct colors for trominoes
TROMINO_COLORS = ['#FF6666', '#66FF66', '#6699FF']

class TrominoTiler:
    def __init__(self, n, missing):
        self.size = 2 ** n
        self.board = np.full((self.size, self.size), -1, dtype=int)
        self.tromino_id = 0
        self.tromino_map = {}  # tromino_id: (color_index, [(x1,y1), (x2,y2), (x3,y3)])
        self.missing = missing
        self.board[missing] = -2  # Mark missing square

    def tile(self):
        self._tile(0, 0, self.size, self.missing[0], self.missing[1])

    def _tile(self, x, y, size, mx, my):
        if size == 2:
            # Place a single tromino in the 2x2, skipping the missing square
            cells = [(x+i, y+j) for i in range(2) for j in range(2) if (x+i, y+j)!=(mx, my)]
            color = self._choose_color(cells)
            self.tromino_map[self.tromino_id] = (color, cells)
            for cx, cy in cells:
                self.board[cx, cy] = self.tromino_id
            self.tromino_id += 1
            return
        # Find center
        mid = size // 2
        # Determine which quadrant the missing square is in
        quad = 0
        if mx < x + mid:
            if my < y + mid:
                quad = 0  # top-left
            else:
                quad = 1  # top-right
        else:
            if my < y + mid:
                quad = 2  # bottom-left
            else:
                quad = 3  # bottom-right
        # Place central tromino
        centers = [
            (x+mid-1, y+mid-1),
            (x+mid-1, y+mid),
            (x+mid, y+mid-1),
            (x+mid, y+mid)
        ]
        tromino_cells = [centers[i] for i in range(4) if i != quad]
        color = self._choose_color(tromino_cells)
        self.tromino_map[self.tromino_id] = (color, tromino_cells)
        for cx, cy in tromino_cells:
            self.board[cx, cy] = self.tromino_id
        tid = self.tromino_id
        self.tromino_id += 1
        # Recurse on each quadrant
        quads = [
            (x, y, x+mid-1, y+mid-1),
            (x, y+mid, x+mid-1, y+size-1),
            (x+mid, y, x+size-1, y+mid-1),
            (x+mid, y+mid, x+size-1, y+size-1)
        ]
        for i, (qx0, qy0, qx1, qy1) in enumerate(quads):
            if i == quad:
                qmx, qmy = mx, my
            else:
                qmx, qmy = centers[i]
            self._tile(qx0, qy0, mid, qmx, qmy)

    def _choose_color(self, cells):
        # For visualization, assign color index in round-robin fashion
        # For coloring constraint, ensure no adjacent trominoes share color
        # Here, we simply alternate colors by tromino_id for simplicity
        # For strict coloring, more logic is needed
        neighbor_colors = set()
        for cx, cy in cells:
            for dx, dy in [(-1,0),(1,0),(0,-1),(0,1)]:
                nx, ny = cx+dx, cy+dy
                if 0 <= nx < self.size and 0 <= ny < self.size:
                    tid = self.board[nx, ny]
                    if tid >= 0:
                        neighbor_colors.add(self.tromino_map[tid][0])
        for color in range(3):
            if color not in neighbor_colors:
                return color
        return 0  # fallback

    def plot(self):
        fig, ax = plt.subplots(figsize=(self.size, self.size))
        for tid, (color, cells) in self.tromino_map.items():
            xs = [c[1] for c in cells]
            ys = [c[0] for c in cells]
            ax.fill_between(xs, [y+0.5 for y in ys], [y-0.5 for y in ys], color=TROMINO_COLORS[color], edgecolor='k', linewidth=1, alpha=0.8)
            for x, y in zip(xs, ys):
                rect = plt.Rectangle((x-0.5, y-0.5), 1, 1, facecolor=TROMINO_COLORS[color], edgecolor='k', linewidth=1)
                ax.add_patch(rect)
        # Draw missing square
        mx, my = self.missing
        rect = plt.Rectangle((my-0.5, mx-0.5), 1, 1, facecolor='white', edgecolor='k', linewidth=2, hatch='//')
        ax.add_patch(rect)
        ax.set_xlim(-0.5, self.size-0.5)
        ax.set_ylim(-0.5, self.size-0.5)
        ax.set_aspect('equal')
        ax.set_xticks(range(self.size))
        ax.set_yticks(range(self.size))
        ax.grid(True, which='both', color='gray', linewidth=0.5, linestyle='--', alpha=0.5)
        plt.gca().invert_yaxis()
        plt.show()

def main():
    n = 5  # Board size 2^n x 2^n
    missing = (2, 3)  # Example missing square (row, col)
    tiler = TrominoTiler(n, missing)
    tiler.tile()
    tiler.plot()

if __name__ == "__main__":
    main()
