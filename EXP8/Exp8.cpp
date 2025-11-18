#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define V 5

int minDistance(const vector<int>& dist, const vector<bool>& sptSet) {
    int min_val = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min_val) {
            min_val = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printSolution(const vector<int>& dist) {
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            cout << i << " \t " << "INF" << endl;
        } else {
            cout << i << " \t " << dist[i] << endl;
        }
    }
}

void dijkstra(const vector<vector<int>>& graph, int src) {
    vector<int> dist(V, INT_MAX);
    vector<bool> sptSet(V, false);

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);

        if (u == -1) break;

        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist);
}

int main() {
    vector<vector<int>> graph = {
        {0, 10, 0, 0, 5},
        {0, 0, 1, 0, 2},
        {0, 0, 0, 4, 0},
        {7, 0, 6, 0, 0},
        {0, 3, 9, 2, 0}
    };

    int source_vertex = 0;

    cout << "Dijkstra's Algorithm - Shortest Path from Source " << source_vertex << endl;
    cout  << endl;
    dijkstra(graph, source_vertex);

    return 0;
}