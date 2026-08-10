#include "triangle.h"

#include <vector>
#include <algorithm>

using namespace std;

TriangleResult triangleCounting(const CSRGraph &csr)
{
    TriangleResult result;

    vector<char> marked(csr.V, false);

    for (int u = 0; u < csr.V; ++u)
    {
        for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; ++i)
        {
            int v = csr.col_idx[i];
            if (v > u)
                marked[v] = true;
        }

        for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; ++i)
        {
            int v = csr.col_idx[i];

            if (v <= u)
                continue;

            for (int j = csr.row_ptr[v]; j < csr.row_ptr[v + 1]; ++j)
            {
                int w = csr.col_idx[j];

                if (w > v && marked[w])
                {
                    ++result.count;
                    result.triangles.push_back({u, v, w});
                }
            }
        }

        for (int i = csr.row_ptr[u]; i < csr.row_ptr[u + 1]; ++i)
        {
            int v = csr.col_idx[i];
            if (v > u)
                marked[v] = false;
        }
    }

    return result;
}
