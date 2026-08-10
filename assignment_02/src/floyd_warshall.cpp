#include "floyd_warshall.h"

#include <limits>
#include <algorithm>

using namespace std;

vector<vector<long long>> buildDistanceMatrix(const CSRGraph &csr)
{
    const long long INF = numeric_limits<long long>::max() / 4;
    vector<vector<long long>> distance(
        csr.V, vector<long long>(csr.V, INF));

    for (int i = 0; i < csr.V; ++i)
        distance[i][i] = 0;

    for (int u = 0; u < csr.V; ++u)
    {
        for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; ++i)
        {
            int v = csr.col_idx[i];
            distance[u][v] =
                min(distance[u][v],
                    static_cast<long long>(csr.weights[i]));
        }
    }

    return distance;
}

FloydWarshallResult floydWarshall(
    const vector<vector<long long>> &initial)
{
    const long long INF = numeric_limits<long long>::max() / 4;

    FloydWarshallResult result;
    result.distance = initial;

    for (int k = 0; k < static_cast<int>(result.distance.size()); ++k)
        for (int i = 0; i < static_cast<int>(result.distance.size()); ++i)
        {
            if (result.distance[i][k] == INF)
                continue;

            for (int j = 0; j < static_cast<int>(result.distance.size()); ++j)
            {
                if (result.distance[k][j] == INF)
                    continue;

                long long candidate =
                    result.distance[i][k] + result.distance[k][j];

                if (candidate < result.distance[i][j])
                    result.distance[i][j] = candidate;
            }
        }

    // Negative-cycle check is part of the timed procedure.
    for (int i = 0; i < static_cast<int>(result.distance.size()); ++i)
    {
        if (result.distance[i][i] < 0)
        {
            result.negativeCycle = true;
            break;
        }
    }

    for (auto &row : result.distance)
        for (long long &value : row)
            if (value == INF)
                value = -1;

    return result;
}
