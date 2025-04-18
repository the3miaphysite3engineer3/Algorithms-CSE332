import java.util.*;

public class HeldKarp {

    static final int INF = Integer.MAX_VALUE;  // Infinity value

    // Function to print the final path (Hamiltonian cycle)
    static void printSolution(int[] path) {
        System.out.println("\nHamiltonian Cycle Found:");
        for (int i = 0; i < path.length; i++) {
            System.out.print(path[i] + " ");
        }
        System.out.println(path[0]);  // To show the cycle (return to the starting vertex)
    }

    // Function to print the adjacency matrix (Graph representation)
    static void printGraph(int[][] graph) {
        System.out.println("Graph Representation (Adjacency Matrix):\n");
        for (int i = 0; i < graph.length; i++) {
            for (int j = 0; j < graph[i].length; j++) {
                System.out.print(graph[i][j] + " ");
            }
            System.out.println();
        }
    }

    // Held-Karp Algorithm to find the minimum cost Hamiltonian Cycle
    static int heldKarp(int[][] graph) {
        int n = graph.length;
        int[][] dp = new int[n][1 << n];  // dp[i][mask] stores the shortest path ending at vertex i with the visited vertices in mask
        int[][] parent = new int[n][1 << n];  // To store the parent of each vertex for path reconstruction

        // Initialize all dp values to infinity
        for (int i = 0; i < n; i++) {
            Arrays.fill(dp[i], INF);
        }

        // Base case: Start from vertex 0 with only vertex 0 visited
        dp[0][1] = 0;

        // Iterate over all subsets of vertices
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 0; u < n; u++) {
                // Skip if u is not in the subset (represented by mask)
                if ((mask & (1 << u)) == 0) continue;

                // Try to find the shortest path ending at u
                for (int v = 0; v < n; v++) {
                    // Skip if v is already in the subset or there's no edge from u to v
                    if ((mask & (1 << v)) != 0 || graph[u][v] == 0) continue;

                    int newMask = mask | (1 << v);
                    int newDist = dp[u][mask] + graph[u][v];
                    if (newDist < dp[v][newMask]) {
                        dp[v][newMask] = newDist;
                        parent[v][newMask] = u;  // Track the parent vertex for path reconstruction
                    }
                }
            }
        }

        // Find the minimum cost Hamiltonian Cycle
        int minCycleCost = INF;
        int lastVertex = -1;
        for (int i = 1; i < n; i++) {
            int cycleCost = dp[i][(1 << n) - 1] + graph[i][0];  // Complete cycle by returning to vertex 0
            if (cycleCost < minCycleCost) {
                minCycleCost = cycleCost;
                lastVertex = i;
            }
        }

        // If no cycle is found, return -1
        if (minCycleCost == INF) {
            System.out.println("Solution does not exist.");
            return -1;
        }

        // Reconstruct the path from the parent array
        int[] path = new int[n];
        int mask = (1 << n) - 1;  // All vertices are visited
        int currVertex = lastVertex;
        for (int i = n - 1; i >= 0; i--) {
            path[i] = currVertex;
            int nextVertex = parent[currVertex][mask];
            mask ^= (1 << currVertex);  // Remove the current vertex from the visited set
            currVertex = nextVertex;
        }

        path[n - 1] = 0;  // Return to the starting vertex
        printSolution(path);
        return minCycleCost;
    }

    // Driver method
    public static void main(String[] args) {
        // Sample graph: adjacency matrix (5 vertices)
        int[][] graph1 = {
                {0, 1, 0, 1, 0},
                {1, 0, 1, 1, 1},
                {0, 1, 0, 0, 1},
                {1, 1, 0, 0, 1},
                {0, 1, 1, 1, 0}
        };

        // Print the graph (adjacency matrix)
        printGraph(graph1);

        // Find and print the Hamiltonian cycle using Held-Karp
        int cycleCost = heldKarp(graph1);
        if (cycleCost != -1) {
            System.out.println("Cost of the Hamiltonian Cycle: " + cycleCost);
        }
    }
}

