#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    vector<Edge> edges;
};

struct Subset {
    int parent;
    int rank;
};

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

void KruskalMST(Graph graph) {
    int V = graph.V;
    vector<Edge> result;
    int e = 0;
    int i = 0;

    sort(graph.edges.begin(), graph.edges.end(), compareEdges);

    Subset* subsets = new Subset[V];
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph.E) {
        Edge next_edge = graph.edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y) {
            result.push_back(next_edge);
            Union(subsets, x, y);
            e++;
        }
    }

    cout << "Ребра минимального остовного дерева:\n";
    int totalWeight = 0;
    for (i = 0; i < e; i++) {
        cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
        totalWeight += result[i].weight;
    }
    cout << "Общий вес остовного дерева: " << totalWeight << endl;

    delete[] subsets;
}

int main() {
    Graph graph;
    graph.V = 6;
    graph.E = 9;

    // Добавляем ребра (src, dest, weight)
    graph.edges = {
        {0, 1, 4}, {0, 2, 4},
        {1, 2, 2}, {1, 0, 4},
        {2, 0, 4}, {2, 1, 2}, {2, 3, 3}, {2, 5, 2}, {2, 4, 4},
        {3, 2, 3}, {3, 4, 3},
        {4, 2, 4}, {4, 3, 3},
        {5, 2, 2}, {5, 4, 3}
    };

    KruskalMST(graph);

    return 0;
}
