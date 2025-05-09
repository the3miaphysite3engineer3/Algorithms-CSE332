#include <iostream>
using namespace std;

#define V 4  // Number of vertices

bool isSafe(int graph[V][V], int color[], int v, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c) {
            return false; // Adjacent vertex has the same color
        }
    }
    return true;
}

bool graphColoringUtil(int graph[V][V], int m, int color[], int v) {
    if (v == V) {
        return true; // All vertices are colored
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(graph, color, v, c)) {
            color[v] = c;  // Assign color
            if (graphColoringUtil(graph, m, color, v + 1)) {
                return true;
            }
            color[v] = 0;  // Backtrack
        }
    }

    return false;
}

int graphColoring(int graph[V][V]) {
    int color[V] = {0}; // Initialize all vertices with no color
    int m=0;

    while(true){
        m++;
        if (!graphColoringUtil(graph, m, color, 0)) {
            cout << "Solution does not exist for "<< m << " colors" << endl;
        } else {
            break;
        }
    }

    cout << "Solution Exists for "<< m << " colors:\nColoring is ";
    for (int i = 0; i < V; i++) {
        cout << color[i] << " ";
    }
    cout << endl;
    return m;
}

/*
int main() {
    int graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int color = 0;  // Number of colors
    color = graphColoring(graph);

    cout<<"number of colors required is "<<color;

    return 0;
}
*/

