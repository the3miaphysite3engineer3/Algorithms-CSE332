

# -------------------------------------------------------------------------------------------------------------------------------------------------------
# This program generates a path through an n x n grid, where n > 2, and plots the path using matplotlib.
# The algorithm traverses the grid in a zigzag manner (greedy algorithm), moving left to right on even rows and right to left on odd rows.
# The path is represented as a list of tuples, where each tuple contains the coordinates of the grid cell.
# The program also includes error handling for invalid inputs and provides a user-friendly interface for inputting the grid size.
# Created by [Michael George] on [25-04-2025].
# -------------------------------------------------------------------------------------------------------------------------------------------------------

import matplotlib.pyplot as plt

def generate_lattice_path(n):
    if n <= 2:
        raise ValueError("n must be greater than 2")
    path = []
    for row in range(n):
        if row % 2 == 0:
            for col in range(n):
                path.append((row, col))
        else:
            for col in reversed(range(n)):
                path.append((row, col))
    return path

def plot_path(path, n):
    x_coords = [p[0] for p in path]  # Rows on x-axis
    y_coords = [p[1] for p in path]  # Columns on y-axis

    plt.figure(figsize=(10, 10))
    plt.plot(x_coords, y_coords, marker='o', linestyle='-')

    for i, (x, y) in enumerate(zip(x_coords, y_coords)):
        plt.text(x, y + 0.1, str(i), fontsize=9, ha='center')

    plt.xticks(range(n))
    plt.yticks(range(n))
    plt.grid(True)
    plt.gca().set_aspect('equal', adjustable='box')
    plt.title(f"{n}x{n} Grid Path Traversal with {2*n - 1} Lines")
    plt.xlabel("Rows")
    plt.ylabel("Columns")
    plt.show()

def main():
    while True:
        try:
            n = int(input("Enter the value of n (n > 2): "))
            if n <= 2:
                print("Value of n must be greater than 2.")
                continue
            else:
                path = generate_lattice_path(n)
                plot_path(path, n)
                break
        except ValueError:
            print("Please enter a valid integer.")
        

if __name__ == "__main__":
    main()
