#include "sssp.h"

#include <queue>
#include <vector>
#include <limits>
#include <utility>

using namespace std;

//---------------------------------------------------------
// SSSP Function (Dijkstra's Algorithm)
//
// Uses a min-priority-queue over (distance, vertex) pairs, exactly the
// way BFS uses a FIFO queue over vertices. Relaxation walks the CSR
// row for u ([row_ptr[u], row_ptr[u+1])) reading both the neighbour
// (col_idx) and its edge weight (weights) at the same index.
//---------------------------------------------------------
SSSPResult SSSP(const CSRGraph &csr, int source)
{
    SSSPResult result;

    const long long INF = numeric_limits<long long>::max();

    result.distance.assign(csr.V, INF);
    result.distance[source] = 0;

    vector<bool> visited(csr.V, false);

    // Min-heap keyed on distance: (distance, vertex)
    priority_queue<
        pair<long long, int>,
        vector<pair<long long, int>>,
        greater<pair<long long, int>>>
        pq;

    pq.push(make_pair(0LL, source));

    while (!pq.empty())
    {
        pair<long long, int> top = pq.top();
        pq.pop();

        long long d = top.first;
        int u = top.second;

        if (visited[u])
        {
            continue;
        }

        visited[u] = true;

        for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; i++)
        {
            int v = csr.col_idx[i];
            int weight = csr.weights[i];

            if (!visited[v] && d + weight < result.distance[v])
            {
                result.distance[v] = d + weight;
                pq.push(make_pair(result.distance[v], v));
            }
        }
    }

    // Mark unreachable vertices as -1 (printed as INF in the output),
    // matching the convention already used by BFS.
    for (int i = 0; i < csr.V; i++)
    {
        if (result.distance[i] == INF)
        {
            result.distance[i] = -1;
        }
    }

    return result;
}
