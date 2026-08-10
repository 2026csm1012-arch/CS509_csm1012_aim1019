#ifndef BFS_H
#define BFS_H

#include "graph.h"
using namespace std;

//---------------------------------------------------------
// Performs Breadth First Search (BFS) on a CSR graph.
//
// Input:
//      csr     - Graph in CSR format
//      source  - Source vertex
//
// Output:
//      Returns:
//          - Traversal Order
//          - Distance of every vertex from source
//---------------------------------------------------------
BFSResult BFS(const CSRGraph &csr, int source);

#endif