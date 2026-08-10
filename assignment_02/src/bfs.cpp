#include "bfs.h"

#include <queue>
#include <vector>

using namespace std;

BFSResult BFS(const CSRGraph &csr, int source)
{
    BFSResult result;

    vector<bool> visited(csr.V, false);

    result.distance.assign(csr.V, -1);


    queue<int> q;


    visited[source] = true;
    result.distance[source] = 0;

    q.push(source);


    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        result.traversal.push_back(u);

        for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; i++)
        {
            int v = csr.col_idx[i];

            if (!visited[v])
            {
                visited[v] = true;
                result.distance[v] = result.distance[u] + 1;

                q.push(v);
            }
        }
    }

    return result;
}