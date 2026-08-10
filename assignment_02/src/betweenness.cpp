#include "betweenness.h"

#include <queue>
#include <vector>

using namespace std;

BetweennessResult betweennessCentrality(const CSRGraph &csr)
{
    BetweennessResult result;
    result.centrality.assign(csr.V, 0.0);

    for (int source = 0; source < csr.V; ++source)
    {
        vector<vector<int>> predecessors(csr.V);
        vector<int> distance(csr.V, -1);
        vector<double> sigma(csr.V, 0.0);
        vector<double> dependency(csr.V, 0.0);
        vector<int> stack;
        queue<int> q;

        distance[source] = 0;
        sigma[source] = 1.0;
        q.push(source);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            stack.push_back(u);

            for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; ++i)
            {
                int v = csr.col_idx[i];

                if (distance[v] < 0)
                {
                    distance[v] = distance[u] + 1;
                    q.push(v);
                }

                if (distance[v] == distance[u] + 1)
                {
                    sigma[v] += sigma[u];
                    predecessors[v].push_back(u);
                }
            }
        }

        while (!stack.empty())
        {
            int w = stack.back();
            stack.pop_back();

            for (int v : predecessors[w])
            {
                if (sigma[w] != 0.0)
                {
                    dependency[v] +=
                        (sigma[v] / sigma[w]) *
                        (1.0 + dependency[w]);
                }
            }

            if (w != source)
                result.centrality[w] += dependency[w];
        }
    }

    for (double &value : result.centrality)
        value /= 2.0;

    return result;
}
