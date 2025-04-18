public class HamiltonianCycle {

    static final int V = 5;

    public static void main(String[] args) {
        boolean[][] graph1 = {
                {false, true,  false, true,  false},
                {true,  false, true,  true,  true },
                {false, true,  false, false, true },
                {true,  true,  false, false, true },
                {false, true,  true,  true,  false}
        };

        boolean[][] graph2 = {
                {false, true,  false, true,  false},
                {true,  false, true,  true,  true },
                {false, true,  false, false, true },
                {true,  true,  false, false, false},
                {false, true,  true,  false, false}
        };

        boolean[][] graph3 = {
                {false, true,  true, false,  false},
                {true,  false, true,  true,  false },
                {true, true,  false, false, true },
                {false,  true,  false, false, true},
                {false, false,  true,  true, false}
        };

        System.out.println("Graph 1:");
        hamCycle(graph1);
        System.out.println("\nGraph 2:");
        hamCycle(graph2);
        System.out.println("\nGraph 3:");
        hamCycle(graph3);
    }

    static boolean isSafe(int v, boolean[][] graph, int[] path, boolean[] visited, int pos) {
        if (!graph[path[pos - 1]][v])
            return false;

        return !visited[v];
    }

    static boolean hamCycleUtil(boolean[][] graph, int[] path, boolean[] visited, int pos) {
        if (pos == V) {
            return graph[path[pos - 1]][path[0]];
        }

        for (int v = 1; v < V; v++) {
            if (isSafe(v, graph, path, visited, pos)) {
                path[pos] = v;
                visited[v] = true;

                if (hamCycleUtil(graph, path, visited, pos + 1))
                    return true;

                // Backtrack
                visited[v] = false;
                path[pos] = -1;
            }
        }

        return false;
    }

    static boolean hamCycle(boolean[][] graph) {
        int[] path = new int[V];
        boolean[] visited = new boolean[V];

        for (int i = 0; i < V; i++) {
            path[i] = -1;
            visited[i] = false;
        }

        path[0] = 0;
        visited[0] = true;

        if (!hamCycleUtil(graph, path, visited, 1)) {
            System.out.println("Solution does not exist");
            return false;
        }

        printSolution(path);
        return true;
    }

    static void printSolution(int[] path) {
        System.out.println("Solution Exists: Following is one Hamiltonian Cycle:");
        for (int v : path) {
            System.out.print(v + " ");
        }
        System.out.println(path[0]); // Complete the cycle
    }
}

