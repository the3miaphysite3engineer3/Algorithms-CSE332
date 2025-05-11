#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define V 8 // number of vertices

int degree(int v, int graph[V][V]) {
    int deg = 0;
    for(int i = 0; i < V; i++) {
        deg += graph[v][i];
    }
    return deg;
}

int DsaturColoring(int graph[V][V]) {
    vector<int> color(V, -1); // -1 means uncolored
    vector<set<int>> neighbor_colors(V); // keeps track of different colors adjacent to each vertex
    vector<bool> colored(V, false);

    for (int step = 0; step < V; ++step) {
        // Find vertex with highest saturation (number of distinct neighbor colors), break ties with degree
        int max_sat = -1, max_deg = -1, chosen = -1;
        for (int v = 0; v < V; ++v) {
            if (colored[v]) continue;
            int sat_deg = neighbor_colors[v].size();
            int deg_v = degree(v, graph);
            if (sat_deg > max_sat || (sat_deg == max_sat && deg_v > max_deg)) {
                max_sat = sat_deg;
                max_deg = deg_v;
                chosen = v;
            }
        }

        // Find the smallest color not used by its neighbors
        set<int> used;
        for (int u = 0; u < V; ++u) {
            if (graph[chosen][u] && (color[u] != -1))
                used.insert(color[u]);
        }

        int c = 0;
        while (used.count(c)) ++c;
        color[chosen] = c;
        colored[chosen] = true;

        // Update neighbor saturation
        for (int u = 0; u < V; ++u) {
            if (graph[chosen][u] && !colored[u])
                neighbor_colors[u].insert(c);
        }
    }

    std::set<int> uniqueColors(color.begin(), color.end());

    // Output results
    cout<<"Vertex Coloring\n";
    for (int i = 0; i < V; ++i)
        cout << "Vertex " << i+1 << " --> Color " << color[i]+1 << '\n';

    return uniqueColors.size();
}

int main() {

    // Graph defined as adjacency matrix
int graph[V][V] = {
    {0, 1, 0, 0, 0, 1, 1, 0}, // 0 connected to 1, 5, and handle 6
    {1, 0, 1, 0, 0, 0, 0, 0}, // 1 connected to 0, 2
    {0, 1, 0, 1, 0, 0, 0, 0}, // 2 connected to 1, 3
    {0, 0, 1, 0, 1, 0, 0, 1}, // 3 connected to 2, 4, and handle 7
    {0, 0, 0, 1, 0, 1, 0, 0}, // 4 connected to 3, 5
    {1, 0, 0, 0, 1, 0, 0, 0}, // 5 connected to 4, 0
    {1, 0, 0, 0, 0, 0, 0, 0}, // handle 6 connected to 0
    {0, 0, 0, 1, 0, 0, 0, 0}  // handle 7 connected to 3
    };
    int n_colors;

    n_colors = DsaturColoring(graph);
    cout<<"number of colors is: "<< n_colors;

    return 0;
}
