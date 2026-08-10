#include "dfs.h"

#include <vector>

//---------------------------------------------------------
// Recursive DFS Helper Function
//---------------------------------------------------------
void DFSUtil(const CSRGraph &csr,
             int vertex,
             std::vector<bool> &visited,
             DFSResult &result)
{
    // Mark current vertex as visited
    visited[vertex] = true;

    // Add to traversal
    result.traversal.push_back(vertex);

    // Visit all neighbours
    for (int i = csr.row_ptr[vertex];
         i < csr.row_ptr[vertex + 1];
         i++)
    {
        int neighbour = csr.col_idx[i];

        if (!visited[neighbour])
        {
            DFSUtil(csr, neighbour, visited, result);
        }
    }
}

//---------------------------------------------------------
// DFS Function
//---------------------------------------------------------
DFSResult DFS(const CSRGraph &csr, int source)
{
    DFSResult result;

    std::vector<bool> visited(csr.V, false);

    DFSUtil(csr, source, visited, result);

    return result;
}