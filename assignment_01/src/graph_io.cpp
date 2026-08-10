#include "graph_io.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

using namespace std;

Graph readGraph(const string &filename, bool weighted)
{
    ifstream fin(filename);

    if (!fin.is_open())
    {
        throw runtime_error("Error: Unable to open input file: " + filename);
    }

    Graph graph;
    graph.weighted = weighted;

    // Read number of vertices and edges
    fin >> graph.V >> graph.E;

    // Allocate the adjacency container that matches the requested format.
    // The reading loop itself is also split via if/else so the two file
    // formats (section 6.1 vs 7.1) are parsed independently.
    if (weighted)
    {
        graph.adjW.resize(graph.V);
    }
    else
    {
        graph.adj.resize(graph.V);
    }

    // Read adjacency list for each vertex
    for (int i = 0; i < graph.V; i++)
    {
        int vertex;
        int degree;

        fin >> vertex >> degree;

        if (weighted)
        {
            // Weighted format: "u degree n1 w1 n2 w2 ..."
            graph.adjW[vertex].resize(degree);

            for (int j = 0; j < degree; j++)
            {
                int neighbour;
                int weight;

                fin >> neighbour >> weight;

                graph.adjW[vertex][j] = make_pair(neighbour, weight);
            }
        }
        else
        {
            // Unweighted format: "u degree n1 n2 n3 ..."
            graph.adj[vertex].resize(degree);

            for (int j = 0; j < degree; j++)
            {
                fin >> graph.adj[vertex][j];
            }
        }
    }

    // Read source vertex
    string sourceLabel;
    fin >> sourceLabel >> graph.source;

    // cout << "Read Label : " << sourceLabel << endl;
    // cout << "Read Source: " << graph.source << endl;

    // Convert to uppercase
    transform(sourceLabel.begin(), sourceLabel.end(),
                   sourceLabel.begin(),
                   [](unsigned char c)
                   {
                       return toupper(c);
                   });

    if (sourceLabel != "SOURCE")
    {
        throw runtime_error("Error: Expected 'SOURCE' in input file.");
    }

    fin.close();

    return graph;
}