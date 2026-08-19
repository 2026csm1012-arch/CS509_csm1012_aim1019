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

struct CSRGraph
{
    int V;
    int E;
    int source;
    bool weighted = false;

    vector<int> row_ptr;
    vector<int> col_idx;

    vector<int> weights;
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

#endif
