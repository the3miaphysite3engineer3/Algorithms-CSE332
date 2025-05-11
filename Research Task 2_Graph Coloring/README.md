# Research Task 2: Graph Coloring

This project explores the **Graph Coloring Problem**, where the goal is to assign colors to the vertices of a graph such that no two adjacent vertices share the same color. The directory contains three implementations of graph coloring algorithms, each with its own approach and complexity.

---

## Overview

### 1. **`backtracking.cpp`**
- **Basic Idea**:  
  Implements a **backtracking algorithm** to solve the graph coloring problem. This approach tries to assign colors to vertices one by one, ensuring no two adjacent vertices share the same color. If a conflict arises, it backtracks and tries a different color.
- **Algorithm Steps**:
  1. Start with the first vertex and assign it the first available color.
  2. Recursively assign colors to the remaining vertices.
  3. If a conflict occurs, backtrack and try the next color.
  4. Repeat until all vertices are colored or no solution exists.
- **Complexity**:
  - **Time Complexity**: O(k^V), where `k` is the number of colors and `V` is the number of vertices. This is due to the exhaustive exploration of all possible color combinations.
  - **Space Complexity**: O(V), for storing the color array and recursion stack.
- **Strengths**: Guarantees an optimal solution (minimum number of colors).
- **Weaknesses**: Computationally expensive for large graphs due to exponential complexity.

---

### 2. **`dsatur.cpp`**
- **Basic Idea**:  
  Implements the **DSATUR (Degree of Saturation)** algorithm, a heuristic-based approach. The algorithm prioritizes vertices with the highest saturation degree (number of distinct colors used by its neighbors). If multiple vertices have the same saturation degree, the vertex with the highest degree (number of neighbors) is chosen.
- **Algorithm Steps**:
  1. Initialize all vertices as uncolored.
  2. At each step, select the uncolored vertex with the highest saturation degree.
  3. Assign the smallest available color that does not conflict with its neighbors.
  4. Update the saturation degree of neighboring vertices.
  5. Repeat until all vertices are colored.
- **Complexity**:
  - **Time Complexity**: O(V^2), where `V` is the number of vertices. This is due to the need to update saturation degrees and find the vertex with the highest saturation at each step.
  - **Space Complexity**: O(V + E), where `E` is the number of edges. This accounts for the adjacency matrix and neighbor color tracking.
- **Strengths**: Efficient for large graphs, uses a greedy approach to minimize colors.
- **Weaknesses**: May not always find the optimal solution (minimum number of colors).

---

### 3. **`powell.cpp`**
- **Basic Idea**:  
  Implements the **Welsh-Powell algorithm**, a greedy approach to graph coloring. The algorithm sorts the vertices by their degree (number of neighbors) in descending order and assigns colors to vertices in that order.
- **Algorithm Steps**:
  1. Sort all vertices in descending order of their degree.
  2. Assign the first available color to each vertex, ensuring no two adjacent vertices share the same color.
  3. Repeat until all vertices are colored.
- **Complexity**:
  - **Time Complexity**: O(V^2), where `V` is the number of vertices. This is due to the adjacency checks for each vertex. Each step however checks adjacent vertices O(V), so the total time complexity is O(V^3).
  - **Space Complexity**: O(V), for storing the color assignments.
- **Strengths**: Simple and efficient for sparse graphs.
- **Weaknesses**: May not always find the optimal solution (minimum number of colors).

---

## Comparison of Algorithms

| Algorithm       | Approach         | Time Complexity | Space Complexity | Strengths                                                                 | Weaknesses                                                              |
|------------------|------------------|------------------|-------------------|--------------------------------------------------------------------------|--------------------------------------------------------------------------|
| **Backtracking** | Exhaustive Search | O(k^V)           | O(V)              | Guarantees an optimal solution (minimum colors).                         | Computationally expensive for large graphs due to exponential complexity. |
| **DSATUR**       | Heuristic         | O(V^2)           | O(V + E)          | Efficient for large graphs, uses a greedy approach to minimize colors.   | May not always find the optimal solution.                                |
| **Welsh-Powell** | Greedy            | O(V^3)           | O(V)              | Simple and efficient for sparse graphs.                                  | May not always find the optimal solution.                                |

---

## Conclusion

This directory provides three distinct approaches to solving the graph coloring problem:
1. **Backtracking**: Guarantees an optimal solution but is computationally expensive for large graphs.
2. **DSATUR**: A heuristic-based approach that is more efficient and practical for larger graphs but may not always find the optimal solution.
3. **Welsh-Powell**: A simple and efficient greedy algorithm, particularly suitable for sparse graphs.

The choice of algorithm depends on the problem size and the need for optimality. For small graphs or when optimality is critical, backtracking is preferred. For larger graphs, DSATUR and Welsh-Powell provide faster and more scalable solutions.