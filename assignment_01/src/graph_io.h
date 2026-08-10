#ifndef GRAPH_IO_H
#define GRAPH_IO_H

#include <string>
#include "graph.h"
using namespace std;

//---------------------------------------------------------
// Reads an adjacency-list graph from file.
//
// Input:
//     filename - path to the input file.
//     weighted - tells the reader which on-disk format to expect:
//                  false -> "u degree n1 n2 n3 ..."          (BFS/DFS, section 6.1)
//                  true  -> "u degree n1 w1 n2 w2 ..."       (SSSP,    section 7.1)
//                Defaults to false so existing BFS/DFS call sites
//                do not need to change.
//
// Output:
//     Returns a Graph whose "weighted" field mirrors the argument and
//     whose "adj" (unweighted) or "adjW" (weighted) list is filled in
//     accordingly.
//---------------------------------------------------------
Graph readGraph(const string &filename, bool weighted = false);

#endif