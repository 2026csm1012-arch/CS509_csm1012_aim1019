#include "csr.h"
using namespace std;

CSRGraph convertToCSR(const Graph &graph)
{
    CSRGraph csr;

    csr.V = graph.V;
    csr.E = graph.E;
    csr.source = graph.source;
    csr.weighted = graph.weighted;

    // row_ptr has V + 1 entries
    csr.row_ptr.resize(csr.V + 1);

    // First entry is always 0
    csr.row_ptr[0] = 0;

    // Compute row_ptr.
    // The degree of each vertex lives in a different container depending
    // on whether the graph is weighted, so row_ptr construction is split
    // with an if/else on graph.weighted.
    if (graph.weighted)
    {
        for (int i = 0; i < csr.V; i++)
        {
            csr.row_ptr[i + 1] = csr.row_ptr[i] + graph.adjW[i].size();
        }
    }
    else
    {
        for (int i = 0; i < csr.V; i++)
        {
            csr.row_ptr[i + 1] = csr.row_ptr[i] + graph.adj[i].size();
        }
    }

    // Total number of adjacency entries
    int totalEdges = csr.row_ptr[csr.V];

    csr.col_idx.resize(totalEdges);

    // Fill col_idx (and, for weighted graphs, the parallel weights array).
    // Again separated with if/else since the source data differs in shape:
    // adj[i] is a list of ints, adjW[i] is a list of (neighbour, weight)
    // pairs.
    if (graph.weighted)
    {
        csr.weights.resize(totalEdges);

        int index = 0;

        for (int i = 0; i < csr.V; i++)
        {
            for (const auto &edge : graph.adjW[i])
            {
                csr.col_idx[index] = edge.first;   // neighbour
                csr.weights[index] = edge.second;  // weight
                index++;
            }
        }
    }
    else
    {
        int index = 0;

        for (int i = 0; i < csr.V; i++)
        {
            for (int neighbour : graph.adj[i])
            {
                csr.col_idx[index++] = neighbour;
            }
        }
    }

    return csr;
}