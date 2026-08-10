#ifndef SSSP_H
#define SSSP_H

#include "graph.h"
using namespace std;

//---------------------------------------------------------
// Performs Single-Source Shortest Path (Dijkstra's algorithm) on a
// weighted CSR graph. All edge weights are assumed to be strictly
// positive, as required by the assignment spec.
//
// Input:
//      csr     - Graph in CSR format (must have csr.weighted == true,
//                i.e. csr.weights populated in parallel with csr.col_idx)
//      source  - Source vertex
//
// Output:
//      Returns:
//          - Shortest distance from source to every vertex.
//            Unreachable vertices are reported as -1.
//---------------------------------------------------------
SSSPResult SSSP(const CSRGraph &csr, int source);

#endif
