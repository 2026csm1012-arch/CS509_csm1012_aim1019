#include "components.h"

#include <queue>
#include <vector>

using namespace std;

ComponentsResult connectedComponents(const CSRGraph &csr)
{
    ComponentsResult result;
    result.component.assign(csr.V, -1);

    for (int start = 0; start < csr.V; ++start)
    {
        if (result.component[start] != -1)
            continue;

        int id = result.count++;
        queue<int> q;

        result.component[start] = id;
        q.push(start);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; ++i)
            {
                int v = csr.col_idx[i];

                if (result.component[v] == -1)
                {
                    result.component[v] = id;
                    q.push(v);
                }
            }
        }
    }

    return result;
}
