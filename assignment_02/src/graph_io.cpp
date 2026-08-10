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
    fin >> graph.V >> graph.E;

    if (weighted)
    {
        graph.adjW.resize(graph.V);
    }
    else
    {
        graph.adj.resize(graph.V);
    }

    for (int i = 0; i < graph.V; i++)
    {
        int vertex;
        int degree;

        fin >> vertex >> degree;

        if (weighted)
        {
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

            graph.adj[vertex].resize(degree);

            for (int j = 0; j < degree; j++)
            {
                fin >> graph.adj[vertex][j];
            }
        }
    }

    graph.source = -1;

    string sourceLabel;
    if (fin >> sourceLabel)
    {
        transform(sourceLabel.begin(), sourceLabel.end(),
                  sourceLabel.begin(),
                  [](unsigned char c)
                  {
                      return static_cast<char>(toupper(c));
                  });

        if (sourceLabel != "SOURCE")
        {
            throw runtime_error("Error: Expected 'SOURCE' in input file.");
        }

        if (!(fin >> graph.source))
            throw runtime_error("Error: Missing source vertex.");
    }

    fin.close();
    return graph;
}