#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include "graph.h"
#include <vector>

std::vector<std::vector<long long>> buildDistanceMatrix(const CSRGraph &csr);
FloydWarshallResult floydWarshall(const std::vector<std::vector<long long>> &initial);

#endif
