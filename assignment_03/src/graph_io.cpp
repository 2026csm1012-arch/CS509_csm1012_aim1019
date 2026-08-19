
#include "common.h"
#include <fstream>
#include <iostream>

bool readMaxflowGraph(const string& fileName, Graph& graph) {
    ifstream file(fileName);

    if (!file) {
        cout << "Error: Cannot open input file: " << fileName << endl;
        return false;
    }

    file >> graph.V >> graph.E;
    graph.adj.resize(graph.V);

    for (int i = 0; i < graph.V; i++) {
        int u, degree;
        file >> u >> degree;

        for (int j = 0; j < degree; j++) {
            int v;
            long long capacity;
            file >> v >> capacity;
            graph.adj[u].push_back({v, capacity});
        }
    }

    string word;
    file >> word >> graph.source;
    file >> word >> graph.sink;

    return true;
}
