#include "bellman_ford.h"

#include <limits>
#include <algorithm>

using namespace std;

BellmanFordResult bellmanFord(const CSRGraph &csr, int source)
{
    const long long INF = numeric_limits<long long>::max() / 4;
    BellmanFordResult result;
    result.distance.assign(csr.V, INF);

    if (source < 0 || source >= csr.V)
        return result;

    result.distance[source] = 0;

    // V-1 relaxation passes over the CSR adjacency entries.
    for (int pass = 1; pass < csr.V; ++pass)
    {
        bool changed = false;

        for (int u = 0; u < csr.V; ++u)
        {
            if (result.distance[u] == INF)
                continue;

            for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; ++i)
            {
                int v = csr.col_idx[i];
                long long candidate =
                    result.distance[u] + csr.weights[i];

                if (candidate < result.distance[v])
                {
                    result.distance[v] = candidate;
                    changed = true;
                }
            }
        }

        if (!changed)
            break;
    }

    // Negative-cycle check is part of the timed algorithm.
    for (int u = 0; u < csr.V; ++u)
    {
        if (result.distance[u] == INF)
            continue;

        for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; ++i)
        {
            int v = csr.col_idx[i];

            if (result.distance[u] + csr.weights[i] < result.distance[v])
            {
                result.negativeCycle = true;
                break;
            }
        }

        if (result.negativeCycle)
            break;
    }

    for (long long &d : result.distance)
        if (d == INF)
            d = -1;

    return result;
}
