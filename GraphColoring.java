import java.util.Arrays;
import java.util.Scanner;

public class GraphColoring {
    private final int vertices;
    private final int[][] graph;
    private int[] colors;
    private int minColors;

    public GraphColoring(int vertices, int[][] graph) {
        this.vertices = vertices;
        this.graph = graph;
        this.colors = new int[vertices];
        this.minColors = Integer.MAX_VALUE;
    }

    public void solve() {
        Arrays.fill(colors, -1);                        // array with -1, indicating that no color has been assigned to any vertex yet.
        tryColoring(0, 1);             // first vertex (index 0) with color 1.
    }

    private void tryColoring(int vertex, int numColors) {                              //  Recursive Function 
        if (numColors >= minColors) return; // Branch and bound condition

        if (vertex == vertices) {
            minColors = numColors;
            printSolution(numColors);
            return;
        }                                               // If all vertices are colored, it updates the minimum colors needed and prints the solution.

        for (int color = 1; color <= numColors; color++) {          // It iterates through all possible colors for the current vertex.
            if (isSafe(vertex, color)) {
                colors[vertex] = color;
                tryColoring(vertex + 1, numColors);
                colors[vertex] = -1; // Backtrack
            }
        }                                                           // After coloring, it backtracks by resetting the color of the current vertex.


        // Try to use a new color
        colors[vertex] = numColors + 1;
        tryColoring(vertex + 1, numColors + 1);
        colors[vertex] = -1;
    }

    private boolean isSafe(int vertex, int color) {                       // The isSafe() method checks if it's safe to color the vertex with the given color.
        for (int i = 0; i < vertices; i++) {
            if (graph[vertex][i] == 1 && colors[i] == color) {
                return false;
            }
        }
        return true;
    }

    private void printSolution(int numColors) {
        System.out.println("Solution found with " + numColors + " colors:");
        for (int i = 0; i < vertices; i++) {
            System.out.println("Vertex " + i + " ---> Color " + colors[i]);
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the number of vertices:");
        int vertices = scanner.nextInt();
        int[][] graph = new int[vertices][vertices];

        System.out.println("Enter the adjacency matrix:");
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                graph[i][j] = scanner.nextInt();
            }
        }

        GraphColoring coloring = new GraphColoring(vertices, graph);
        coloring.solve();
    }
}
