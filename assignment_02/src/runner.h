#ifndef RUNNER_H
#define RUNNER_H

#include <functional>
#include <string>

#include "graph.h"

//---------------------------------------------------------
// Generic Runner
//
// "weighted" tells the runner which on-disk adjacency-list format to
// read (see graph_io.h): false for BFS/DFS-style unweighted files,
// true for SSSP-style weighted files. It defaults to false so the
// existing BFS/DFS call sites keep working unchanged.
//---------------------------------------------------------
void runAlgorithm(
    const std::string &algorithmName,
    function<double(const CSRGraph &, int, const string &)> executor,
    bool weighted = false);

//---------------------------------------------------------
// Breadth First Search
//---------------------------------------------------------
void runBFS();

//---------------------------------------------------------
// Depth First Search
//---------------------------------------------------------
void runDFS();

//---------------------------------------------------------
// Single Source Shortest Path
//---------------------------------------------------------
void runSSSP();


#endif
void runBellmanFord();
void runFloydWarshall();
void runTriangleCounting();
void runBetweennessCentrality();
void runConnectedComponents();
