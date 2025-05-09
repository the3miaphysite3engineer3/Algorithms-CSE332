#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define V 8  // Number of vertices

// Structure to store a vertex and its degree
struct Vertex {
    int id;
    int degree;
};

// Function to sort vertices by degree in descending order
bool compare(Vertex a, Vertex b) {
    return a.degree > b.degree;
}

// Welsh-Powell Algorithm
void welshPowell(int graph[V][V]) {
    vector<Vertex> vertices(V);
    vector<int> color(V, 0); // Color array, initialized to 0 (uncolored)
    int currentColor = 0;

    // Compute degrees of all vertices
    for (int i = 0; i < V; i++) {
        vertices[i].id = i;
        vertices[i].degree = 0;
        for (int j = 0; j < V; j++) {
            if (graph[i][j] == 1) vertices[i].degree++;
        }
    }

    // Sort vertices by degree in descending order
    sort(vertices.begin(), vertices.end(), compare);

    // Assign colors
    for (int i = 0; i < V; i++) {
        if (color[vertices[i].id] == 0) { // If not colored
            currentColor++;
            color[vertices[i].id] = currentColor;

            // Color other vertices that are not adjacent
            for (int j = i + 1; j < V; j++) {
                if (color[vertices[j].id] == 0) { // If not colored
                    bool canColor = true;
                    for (int k = 0; k < V; k++) {
                        if (graph[vertices[j].id][k] == 1 && color[k] == currentColor) {
                            canColor = false; // Adjacent vertex already has the current color
                            break;
                        }
                    }
                    if (canColor) {
                        color[vertices[j].id] = currentColor;
                    }
                }
            }
        }
    }

    // Print the coloring result
    cout << "Vertex Coloring:\n";
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i+1 << " --> Color " << color[i] << endl;
    }
    cout << "number of colors is: "<< currentColor;
}

/*
int main() {
    int graph[8][8] = {
    {0, 1, 0, 0, 0, 1, 1, 0}, // 0 connected to 1, 5, and handle 6
    {1, 0, 1, 0, 0, 0, 0, 0}, // 1 connected to 0, 2
    {0, 1, 0, 1, 0, 0, 0, 0}, // 2 connected to 1, 3
    {0, 0, 1, 0, 1, 0, 0, 1}, // 3 connected to 2, 4, and handle 7
    {0, 0, 0, 1, 0, 1, 0, 0}, // 4 connected to 3, 5
    {1, 0, 0, 0, 1, 0, 0, 0}, // 5 connected to 4, 0
    {1, 0, 0, 0, 0, 0, 0, 0}, // handle 6 connected to 0
    {0, 0, 0, 1, 0, 0, 0, 0}  // handle 7 connected to 3
    };

    welshPowell(graph);

    return 0;
}
*/

