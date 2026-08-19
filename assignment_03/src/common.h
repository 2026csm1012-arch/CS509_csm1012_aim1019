
#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

using namespace std;

struct Edge {
    int to;
    long long capacity;
};

struct Graph {
    int V;
    int E;
    vector<vector<Edge>> adj;
    int source;
    int sink;
};

struct CutEdge {
    int u;
    int v;
    long long capacity;
};

struct GDResult {
    int degree;
    double x;
    double fx;
    int iterations;
    bool converged;
};

struct FlowResult {
    long long maxFlow;
    long long minCut;
    vector<int> sourceSide;
    vector<int> sinkSide;
    vector<CutEdge> cutEdges;
};

bool readMaxflowGraph(const string& fileName, Graph& graph);

GDResult gradientDescent(const vector<double>& c, double x, double rate,
                         double tolerance, int maxIterations);

FlowResult maxflow(const Graph& graph);

#endif
