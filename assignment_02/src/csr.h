#ifndef CSR_H
#define CSR_H

#include "graph.h"

//---------------------------------------------------------
// Converts an adjacency-list graph into CSR format.
//
// Input:
//     graph - Graph stored as an adjacency list.
//
// Output:
//     Returns a CSRGraph.
//---------------------------------------------------------
CSRGraph convertToCSR(const Graph &graph);

#endif