#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
using namespace std;

struct Graph
{
    int V;
    int E;
    int source;
    bool weighted = false;

    vector<vector<int>> adj;

    vector<vector<pair<int, int>>> adjW;
};

// Graph Representation using Compressed Sparse Row (CSR) format
//
// CSRGraph is the single, global CSR representation shared by every
// algorithm (BFS, DFS, SSSP). row_ptr/col_idx describe the structure
// exactly as before; "weights" is an additional parallel array that is
// only filled in when the source Graph was weighted. Every entry
// weights[i] corresponds to the edge col_idx[i], so
// (col_idx[i], weights[i]) is the (neighbour, weight) pair for that
// CSR slot.
struct CSRGraph
{
    int V;
    int E;
    int source;
    bool weighted = false;

    vector<int> row_ptr;
    vector<int> col_idx;

    // Only populated when weighted == true. Same size/order as col_idx.
    vector<int> weights;
};


struct BFSResult
{
    vector<int> traversal;
    vector<int> distance;
};



struct DFSResult
{
    std::vector<int> traversal;
};


struct BellmanFordResult
{
    vector<long long> distance;
    bool negativeCycle = false;
};

struct FloydWarshallResult
{
    vector<vector<long long>> distance;
    bool negativeCycle = false;
};

struct TriangleResult
{
    long long count = 0;
    vector<vector<int>> triangles;
};

struct BetweennessResult
{
    vector<double> centrality;
};

struct ComponentsResult
{
    int count = 0;
    vector<int> component;
};

struct SSSPResult
{
    // distance[i] holds the shortest distance from the source to vertex i.
    // Unreachable vertices are marked as -1 (printed as INF in output).
    vector<long long> distance;
};

#endif