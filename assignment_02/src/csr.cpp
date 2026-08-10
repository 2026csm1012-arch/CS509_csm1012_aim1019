#include "csr.h"
using namespace std;

CSRGraph convertToCSR(const Graph &graph)
{
    CSRGraph csr;

    csr.V = graph.V;
    csr.E = graph.E;
    csr.source = graph.source;
    csr.weighted = graph.weighted;
 
    csr.row_ptr.resize(csr.V + 1);
 
    csr.row_ptr[0] = 0;
 
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
    int totalEdges = csr.row_ptr[csr.V];

    csr.col_idx.resize(totalEdges);
 
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