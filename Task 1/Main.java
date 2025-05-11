import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.util.List;

public class Main {
    // Define colors for visualization
    private static final Color[] COLORS = {
        new Color(255, 87, 51),  // Red
        new Color(51, 255, 87),  // Green
        new Color(51, 87, 255)   // Blue
    };
    private static final Color BLACK = Color.BLACK;

    // Board class to represent the 2^n x 2^n grid
    static class Board {
        int size;
        int[][] board;
        int[][] colorBoard;
        int trominoCount;

        public Board(int n, Integer missingX, Integer missingY) {
            this.size = (int) Math.pow(2, n);
            this.board = new int[size][size];
            this.colorBoard = new int[size][size];
            this.trominoCount = 0;

            // Initialize board with zeros
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    board[i][j] = 0;
                    colorBoard[i][j] = 0;
                }
            }

            // Set missing square
            int mx = (missingX == null) ? new Random().nextInt(size) : missingX;
            int my = (missingY == null) ? new Random().nextInt(size) : missingY;
            board[my][mx] = -1;
        }

        public void placeTromino(int x, int y, int missingX, int missingY, int size, String algorithmName) {
            if (size == 2) {
                // Base case: place a single tromino in a 2x2 board
                trominoCount++;
                for (int i = y; i < y + 2; i++) {
                    for (int j = x; j < x + 2; j++) {
                        if (i != missingY || j != missingX) {
                            board[i][j] = trominoCount;
                        }
                    }
                }
                return;
            }

            // Find the quadrant of the missing square
            int half = size / 2;
            int centerX = x + half - 1;
            int centerY = y + half - 1;

            // Determine which quadrant contains the missing square
            int quadX = (missingX > centerX) ? 1 : 0;
            int quadY = (missingY > centerY) ? 1 : 0;

            // Place the central tromino
            trominoCount++;
            int centralTrominoId = trominoCount;

            // Place tromino in the center, covering one square in each quadrant except the one with the missing square
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    if (i != quadY || j != quadX) {
                        int newY = centerY + i;
                        int newX = centerX + j;
                        board[newY][newX] = centralTrominoId;
                    }
                }
            }

            // Recursively tile each quadrant
            // Upper left quadrant
            int newMissingY = (quadY == 0 && quadX == 0) ? missingY : centerY;
            int newMissingX = (quadY == 0 && quadX == 0) ? missingX : centerX;
            placeTromino(x, y, newMissingX, newMissingY, half, algorithmName);

            // Upper right quadrant
            newMissingY = (quadY == 0 && quadX == 1) ? missingY : centerY;
            newMissingX = (quadY == 0 && quadX == 1) ? missingX : centerX + 1;
            placeTromino(x + half, y, newMissingX, newMissingY, half, algorithmName);

            // Lower left quadrant
            newMissingY = (quadY == 1 && quadX == 0) ? missingY : centerY + 1;
            newMissingX = (quadY == 1 && quadX == 0) ? missingX : centerX;
            placeTromino(x, y + half, newMissingX, newMissingY, half, algorithmName);

            // Lower right quadrant
            newMissingY = (quadY == 1 && quadX == 1) ? missingY : centerY + 1;
            newMissingX = (quadY == 1 && quadX == 1) ? missingX : centerX + 1;
            placeTromino(x + half, y + half, newMissingX, newMissingY, half, algorithmName);
        }

        public void visualize(Graphics g, int panelWidth, int panelHeight, String title, int offsetX) {
            int cellSize = Math.min(panelWidth, panelHeight) / size;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    Color color = BLACK;
                    if (board[i][j] == -1) {
                        color = BLACK;
                    } else if (board[i][j] > 0) {
                        int colorIdx = colorBoard[i][j] - 1;
                        color = COLORS[colorIdx % COLORS.length];
                    }
                    g.setColor(color);
                    g.fillRect(offsetX + j * cellSize, i * cellSize, cellSize, cellSize);
                    g.setColor(BLACK);
                    g.drawRect(offsetX + j * cellSize, i * cellSize, cellSize, cellSize);
                }
            }
            g.setColor(BLACK);
            g.drawString(title, offsetX + 10, 20);
        }
    }

    // Divide and Conquer Algorithm with Color Assignment
    static class DivideAndConquerAlgorithm {
        private Board board;

        public DivideAndConquerAlgorithm(int n, Integer missingX, Integer missingY) {
            this.board = new Board(n, missingX, missingY);
        }

        public Board run() {
            // Find missing square position
            int missingX = -1, missingY = -1;
            for (int i = 0; i < board.size; i++) {
                for (int j = 0; j < board.size; j++) {
                    if (board.board[i][j] == -1) {
                        missingY = i;
                        missingX = j;
                        break;
                    }
                }
            }

            // Place trominoes
            board.placeTromino(0, 0, missingX, missingY, board.size, "Divide and Conquer");

            // Assign colors
            assignColors();
            return board;
        }

        private void assignColors() {
            // Build adjacency graph
            Map<Integer, Set<Integer>> adjacency = new HashMap<>();
            Map<Integer, List<int[]>> trominoPositions = new HashMap<>();

            // Initialize adjacency and positions
            for (int i = 1; i <= board.trominoCount; i++) {
                adjacency.put(i, new HashSet<>());
                trominoPositions.put(i, new ArrayList<>());
            }

            // Find tromino positions
            for (int i = 0; i < board.size; i++) {
                for (int j = 0; j < board.size; j++) {
                    int trominoId = board.board[i][j];
                    if (trominoId > 0) {
                        trominoPositions.get(trominoId).add(new int[]{i, j});
                    }
                }
            }

            // Directions for adjacency check
            int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

            // Build adjacency graph (ensure symmetry)
            for (int trominoId : trominoPositions.keySet()) {
                for (int[] pos : trominoPositions.get(trominoId)) {
                    int i = pos[0], j = pos[1];
                    for (int[] dir : directions) {
                        int ni = i + dir[0], nj = j + dir[1];
                        if (ni >= 0 && ni < board.size && nj >= 0 && nj < board.size) {
                            int neighborId = board.board[ni][nj];
                            if (neighborId > 0 && neighborId != trominoId) {
                                // Add both directions to ensure symmetry
                                adjacency.get(trominoId).add(neighborId);
                                adjacency.get(neighborId).add(trominoId);
                            }
                        }
                    }
                }
            }

            // Welsh-Powell coloring
            Map<Integer, Integer> colors = new HashMap<>();
            List<Integer> trominoIds = new ArrayList<>();
            for (int i = 1; i <= board.trominoCount; i++) {
                trominoIds.add(i);
            }
            trominoIds.sort((a, b) -> Integer.compare(adjacency.get(b).size(), adjacency.get(a).size()));

            for (int trominoId : trominoIds) {
                Set<Integer> usedColors = new HashSet<>();
                for (int adj : adjacency.get(trominoId)) {
                    if (colors.containsKey(adj)) {
                        usedColors.add(colors.get(adj));
                    }
                }
                int color = 1;
                while (usedColors.contains(color) && color <= 3) {
                    color++;
                }
                if (color > 3) {
                    // If no color is available, assign the first color (will be fixed by backtracking)
                    color = 1;
                }
                colors.put(trominoId, color);
            }

            // Verify coloring
            boolean validColoring = true;
            for (int trominoId : adjacency.keySet()) {
                for (int neighbor : adjacency.get(trominoId)) {
                    if (Objects.equals(colors.get(trominoId), colors.get(neighbor))) {
                        validColoring = false;
                        break;
                    }
                }
                if (!validColoring) break;
            }

            if (!validColoring) {
                backtrackingColoring(adjacency);
            } else {
                // Apply colors to board
                for (int i = 0; i < board.size; i++) {
                    for (int j = 0; j < board.size; j++) {
                        if (board.board[i][j] > 0) {
                            board.colorBoard[i][j] = colors.getOrDefault(board.board[i][j], 1);
                        }
                    }
                }
            }
        }

        private void backtrackingColoring(Map<Integer, Set<Integer>> adjacency) {
            Map<Integer, Integer> colors = new HashMap<>();

            class Backtrack {
                boolean backtrack(int trominoId) {
                    if (trominoId > board.trominoCount) {
                        return true;
                    }
                    for (int color = 1; color <= 3; color++) {
                        if (isValidColor(trominoId, color, adjacency, colors)) {
                            colors.put(trominoId, color);
                            if (backtrack(trominoId + 1)) {
                                return true;
                            }
                            colors.remove(trominoId);
                        }
                    }
                    return false;
                }

                boolean isValidColor(int trominoId, int color, Map<Integer, Set<Integer>> adjacency, Map<Integer, Integer> colors) {
                    for (int neighbor : adjacency.get(trominoId)) {
                        if (colors.containsKey(neighbor) && colors.get(neighbor) == color) {
                            return false;
                        }
                    }
                    return true;
                }
            }

            new Backtrack().backtrack(1);

            // Apply colors to board
            for (int i = 0; i < board.size; i++) {
                for (int j = 0; j < board.size; j++) {
                    if (board.board[i][j] > 0) {
                        board.colorBoard[i][j] = colors.getOrDefault(board.board[i][j], 1);
                    }
                }
            }
        }
    }

    // Graph Coloring Algorithm
    static class GraphColoringAlgorithm {
        private Board board;
        private Map<Integer, Set<Integer>> adjacencyGraph;
        private Map<Integer, Integer> colors;

        public GraphColoringAlgorithm(int n, Integer missingX, Integer missingY) {
            this.board = new Board(n, missingX, missingY);
            this.colors = new HashMap<>();
        }

        public Board run() {
            // Find missing square position
            int missingX = -1, missingY = -1;
            for (int i = 0; i < board.size; i++) {
                for (int j = 0; j < board.size; j++) {
                    if (board.board[i][j] == -1) {
                        missingY = i;
                        missingX = j;
                        break;
                    }
                }
            }

            // Place trominoes
            board.placeTromino(0, 0, missingX, missingY, board.size, "Graph Coloring");

            // Build adjacency graph
            adjacencyGraph = buildAdjacencyGraph();

            // Solve CSP
            solveCsp(1);

            // Apply colors to board
            for (int i = 0; i < board.size; i++) {
                for (int j = 0; j < board.size; j++) {
                    if (board.board[i][j] > 0) {
                        board.colorBoard[i][j] = colors.getOrDefault(board.board[i][j], 1);
                    }
                }
            }
            return board;
        }

        private Map<Integer, Set<Integer>> buildAdjacencyGraph() {
            Map<Integer, Set<Integer>> adjacency = new HashMap<>();
            for (int i = 1; i <= board.trominoCount; i++) {
                adjacency.put(i, new HashSet<>());
            }

            // Horizontal adjacencies
            for (int i = 0; i < board.size; i++) {
                for (int j = 0; j < board.size - 1; j++) {
                    int id1 = board.board[i][j];
                    int id2 = board.board[i][j + 1];
                    if (id1 > 0 && id2 > 0 && id1 != id2) {
                        adjacency.get(id1).add(id2);
                        adjacency.get(id2).add(id1);
                    }
                }
            }

            // Vertical adjacencies
            for (int i = 0; i < board.size - 1; i++) {
                for (int j = 0; j < board.size; j++) {
                    int id1 = board.board[i][j];
                    int id2 = board.board[i + 1][j];
                    if (id1 > 0 && id2 > 0 && id1 != id2) {
                        adjacency.get(id1).add(id2);
                        adjacency.get(id2).add(id1);
                    }
                }
            }
            return adjacency;
        }

        private boolean solveCsp(int trominoId) {
            if (trominoId > board.trominoCount) {
                return true;
            }
            for (int color = 1; color <= 3; color++) {
                if (isValidColor(trominoId, color)) {
                    colors.put(trominoId, color);
                    if (solveCsp(trominoId + 1)) {
                        return true;
                    }
                    colors.remove(trominoId);
                }
            }
            return false;
        }

        private boolean isValidColor(int trominoId, int color) {
            for (int adj : adjacencyGraph.get(trominoId)) {
                if (colors.containsKey(adj) && colors.get(adj) == color) {
                    return false;
                }
            }
            return true;
        }
    }

    // SAT Solver Algorithm (Simplified)
    static class SATSolverAlgorithm {
        private Board board;
        private Map<Integer, Integer> colors;

        public SATSolverAlgorithm(int n, Integer missingX, Integer missingY) {
            this.board = new Board(n, missingX, missingY);
            this.colors = new HashMap<>();
        }

        public Board run() {
            // Find missing square position
            int missingX = -1, missingY = -1;
            for (int i = 0; i < board.size; i++) {
                for (int j = 0; j < board.size; j++) {
                    if (board.board[i][j] == -1) {
                        missingY = i;
                        missingX = j;
                        break;
                    }
                }
            }

            // Place trominoes
            board.placeTromino(0, 0, missingX, missingY, board.size, "SAT Solver Approach");

            // Build adjacency graph
            Map<Integer, Set<Integer>> adjacency = buildAdjacencyGraph();

            // Solve SAT model
            solveSatModel(adjacency, 1);

            // Apply colors to board
            for (int i = 0; i < board.size; i++) {
                for (int j = 0; j < board.size; j++) {
                    if (board.board[i][j] > 0) {
                        board.colorBoard[i][j] = colors.getOrDefault(board.board[i][j], 1);
                    }
                }
            }
            return board;
        }

        private Map<Integer, Set<Integer>> buildAdjacencyGraph() {
            Map<Integer, Set<Integer>> adjacency = new HashMap<>();
            for (int i = 1; i <= board.trominoCount; i++) {
                adjacency.put(i, new HashSet<>());
            }

            // Horizontal adjacencies
            for (int i = 0; i < board.size; i++) {
                for (int j = 0; j < board.size - 1; j++) {
                    int id1 = board.board[i][j];
                    int id2 = board.board[i][j + 1];
                    if (id1 > 0 && id2 > 0 && id1 != id2) {
                        adjacency.get(id1).add(id2);
                        adjacency.get(id2).add(id1);
                    }
                }
            }

            // Vertical adjacencies
            for (int i = 0; i < board.size - 1; i++) {
                for (int j = 0; j < board.size; j++) {
                    int id1 = board.board[i][j];
                    int id2 = board.board[i + 1][j];
                    if (id1 > 0 && id2 > 0 && id1 != id2) {
                        adjacency.get(id1).add(id2);
                        adjacency.get(id2).add(id1);
                    }
                }
            }
            return adjacency;
        }

        private boolean solveSatModel(Map<Integer, Set<Integer>> adjacency, int trominoId) {
            if (trominoId > board.trominoCount) {
                return true;
            }
            for (int color = 1; color <= 3; color++) {
                if (isValidColor(adjacency, trominoId, color)) {
                    colors.put(trominoId, color);
                    if (solveSatModel(adjacency, trominoId + 1)) {
                        return true;
                    }
                    colors.remove(trominoId);
                }
            }
            return false;
        }

        private boolean isValidColor(Map<Integer, Set<Integer>> adjacency, int trominoId, int color) {
            for (int adj : adjacency.get(trominoId)) {
                if (colors.containsKey(adj) && colors.get(adj) == color) {
                    return false;
                }
            }
            return true;
        }
    }

    // Visualization Panel
    static class VisualizationPanel extends JPanel {
        private final List<Board> boards;
        private final List<String> titles;

        public VisualizationPanel(List<Board> boards, List<String> titles) {
            this.boards = boards;
            this.titles = titles;
            setPreferredSize(new Dimension(boards.size() * 400, 400));
        }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            for (int i = 0; i < boards.size(); i++) {
                boards.get(i).visualize(g, 400, 400, titles.get(i), i * 400);
            }
        }
    }

    // Run all algorithms and display results
    public static void runAllAlgorithms(int n, Integer missingX, Integer missingY) {
        List<Object[]> algorithms = Arrays.asList(
            new Object[]{"Divide and Conquer", DivideAndConquerAlgorithm.class},
            new Object[]{"Graph Coloring", GraphColoringAlgorithm.class},
            new Object[]{"SAT Solver Approach", SATSolverAlgorithm.class}
        );

        List<Board> boards = new ArrayList<>();
        List<String> titles = new ArrayList<>();
        List<Double> executionTimes = new ArrayList<>();

        for (Object[] algo : algorithms) {
            String name = (String) algo[0];
            @SuppressWarnings("unchecked")
            Class<?> algoClass = (Class<?>) algo[1];

            // Initialize algorithm
            Board board;
            long startTime = System.nanoTime();
            try {
                if (algoClass == DivideAndConquerAlgorithm.class) {
                    board = new DivideAndConquerAlgorithm(n, missingX, missingY).run();
                } else if (algoClass == GraphColoringAlgorithm.class) {
                    board = new GraphColoringAlgorithm(n, missingX, missingY).run();
                } else {
                    board = new SATSolverAlgorithm(n, missingX, missingY).run();
                }
            } catch (Exception e) {
                System.err.println("Error running " + name + ": " + e.getMessage());
                continue;
            }
            long endTime = System.nanoTime();

            // Calculate execution time in seconds
            double execTime = (endTime - startTime) / 1_000_000_000.0;
            executionTimes.add(execTime);

            boards.add(board);
            titles.add(name + "\nExecution Time: " + String.format("%.4f", execTime) + " seconds");
        }

        // Display execution times
        System.out.println("\nExecution Times:");
        for (int i = 0; i < algorithms.size(); i++) {
            String name = (String) algorithms.get(i)[0];
            System.out.printf("%s: %.4f seconds%n", name, executionTimes.get(i));
        }

        // Create visualization window
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("L-Tromino Tiling");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.add(new VisualizationPanel(boards, titles));
            frame.pack();
            frame.setVisible(true);
        });
    }

    // Compare algorithm performance with different board sizes
    public static void compareAlgorithmPerformance(int maxN) {
        System.out.println("\nComparing Algorithm Performance:");
        System.out.println("-".repeat(80));
        System.out.printf("%-15s%-25s%-25s%-25s%n", "Board Size", "Divide and Conquer", "Graph Coloring", "SAT Solver");
        System.out.println("-".repeat(80));

        for (int n = 1; n <= maxN; n++) {
            Integer missingX = 0, missingY = 0;
            double[] times = new double[3];

            // Run each algorithm
            Class<?>[] algoClasses = {DivideAndConquerAlgorithm.class, GraphColoringAlgorithm.class, SATSolverAlgorithm.class};
            for (int i = 0; i < algoClasses.length; i++) {
                long startTime = System.nanoTime();
                try {
                    if (algoClasses[i] == DivideAndConquerAlgorithm.class) {
                        new DivideAndConquerAlgorithm(n, missingX, missingY).run();
                    } else if (algoClasses[i] == GraphColoringAlgorithm.class) {
                        new GraphColoringAlgorithm(n, missingX, missingY).run();
                    } else {
                        new SATSolverAlgorithm(n, missingX, missingY).run();
                    }
                } catch (Exception e) {
                    System.err.println("Error in performance comparison: " + e.getMessage());
                }
                long endTime = System.nanoTime();
                times[i] = (endTime - startTime) / 1_000_000_000.0;
            }

            String boardSize = (int) Math.pow(2, n) + "x" + (int) Math.pow(2, n);
            System.out.printf("%-15s%-25.6f%-25.6f%-25.6f%n", boardSize, times[0], times[1], times[2]);
        }
        System.out.println("-".repeat(80));
    }

    public static void main(String[] args) {
        // Run visual demonstration with n=3 (8x8 board)
        runAllAlgorithms(3, 2, 3);

        // Compare performance up to n=3
        compareAlgorithmPerformance(3);
    }
}
