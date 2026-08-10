#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
using namespace std;

// Graph Representation using Adjacency List
//
// The same Graph struct is used for BOTH unweighted (BFS/DFS) and
// weighted (SSSP) inputs. The "weighted" flag tells every downstream
// consumer (CSR conversion, algorithms, etc.) which of the two
// adjacency containers below is actually populated:
//
//   weighted == false -> "adj"  is populated  (plain neighbour lists)
//   weighted == true  -> "adjW" is populated  (neighbour, weight) pairs
struct Graph
{
    int V;
    int E;
    int source;
    bool weighted = false;

    // Unweighted adjacency list: adj[u] = { neighbours of u }
    vector<vector<int>> adj;

    // Weighted adjacency list: adjW[u] = { (neighbour, weight), ... }
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


struct SSSPResult
{
    // distance[i] holds the shortest distance from the source to vertex i.
    // Unreachable vertices are marked as -1 (printed as INF in output).
    vector<long long> distance;
};

#endif