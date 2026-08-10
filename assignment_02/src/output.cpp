#include "output.h"

#include <fstream>
#include <iomanip>
#include <stdexcept>

//------------------------------------------------------
// Write BFS Output
//------------------------------------------------------
void writeBFSOutput(const std::string &filename,
                    const BFSResult &result,
                    int source)
{
    std::ofstream fout(filename);

    if (!fout.is_open())
        throw std::runtime_error("Unable to create output file.");

    fout << "Algorithm: BFS\n\n";

    fout << "Source: " << source << "\n\n";

    fout << "Traversal: ";

    for (size_t i = 0; i < result.traversal.size(); i++)
    {
        fout << result.traversal[i];

        if (i + 1 != result.traversal.size())
            fout << " ";
    }

    fout << "\n\n";

    fout << "Distances:\n";

    for (size_t i = 0; i < result.distance.size(); i++)
    {
        fout << i << " ";

        if (result.distance[i] == -1)
            fout << "INF";
        else
            fout << result.distance[i];

        fout << "\n";
    }
}

//------------------------------------------------------
// Write DFS Output
//------------------------------------------------------
void writeDFSOutput(const std::string &filename,
                    const DFSResult &result,
                    int source)
{
    std::ofstream fout(filename);

    if (!fout.is_open())
        throw std::runtime_error("Unable to create output file.");

    fout << "Algorithm: DFS\n\n";

    fout << "Source: " << source << "\n\n";

    fout << "Traversal: ";

    for (size_t i = 0; i < result.traversal.size(); i++)
    {
        fout << result.traversal[i];

        if (i + 1 != result.traversal.size())
            fout << " ";
    }

    fout << "\n";
}

//------------------------------------------------------
// Write SSSP Output
//------------------------------------------------------
void writeSSSPOutput(const std::string &filename,
                    const SSSPResult &result,
                    int source)
{
    std::ofstream fout(filename);

    if (!fout.is_open())
        throw std::runtime_error("Unable to create output file.");

    fout << "Algorithm: SSSP\n\n";

    fout << "Source: " << source << "\n\n";

    fout << "Vertex\tDistance\n";

    for (size_t i = 0; i < result.distance.size(); i++)
    {
        fout << i << "\t";

        if (result.distance[i] == -1)
            fout << "INF";
        else
            fout << result.distance[i];

        fout << "\n";
    }
}
//------------------------------------------------------
// Bellman-Ford Output
//------------------------------------------------------
void writeBellmanFordOutput(const std::string &filename,
                            const BellmanFordResult &result,
                            int source)
{
    std::ofstream fout(filename);
    if (!fout.is_open())
        throw std::runtime_error("Unable to create output file.");

    fout << "Algorithm: Bellman-Ford\n\n";
    fout << "Source: " << source << "\n\n";

    if (result.negativeCycle)
    {
        fout << "Negative cycle detected\n";
        return;
    }

    fout << "Vertex\tDistance\n";
    for (size_t i = 0; i < result.distance.size(); ++i)
    {
        fout << i << "\t";
        if (result.distance[i] == -1)
            fout << "INF";
        else
            fout << result.distance[i];
        fout << "\n";
    }
}

//------------------------------------------------------
// Floyd-Warshall Output
//------------------------------------------------------
void writeFloydWarshallOutput(const std::string &filename,
                              const FloydWarshallResult &result)
{
    std::ofstream fout(filename);
    if (!fout.is_open())
        throw std::runtime_error("Unable to create output file.");

    fout << "Algorithm: Floyd-Warshall\n\n";

    if (result.negativeCycle)
    {
        fout << "Negative cycle detected\n";
        return;
    }

    fout << "Distance Matrix:\n";
    for (size_t i = 0; i < result.distance.size(); ++i)
    {
        for (size_t j = 0; j < result.distance[i].size(); ++j)
        {
            if (result.distance[i][j] == -1)
                fout << "INF";
            else
                fout << result.distance[i][j];

            if (j + 1 != result.distance[i].size())
                fout << " ";
        }
        fout << "\n";
    }
}

//------------------------------------------------------
// Triangle Counting Output
//------------------------------------------------------
void writeTriangleOutput(const std::string &filename,
                         const TriangleResult &result)
{
    std::ofstream fout(filename);
    if (!fout.is_open())
        throw std::runtime_error("Unable to create output file.");

    fout << "Algorithm: Triangle Counting\n\n";
    fout << "Total triangles: " << result.count << "\n";

    // Listing all triangles is useful for small graphs and remains
    // deterministic because CSR adjacency order is preserved.
    fout << "Triangles found:\n";
    for (const auto &triangle : result.triangles)
    {
        fout << "("
             << triangle[0] << ", "
             << triangle[1] << ", "
             << triangle[2] << ")\n";
    }
}

//------------------------------------------------------
// Betweenness Centrality Output
//------------------------------------------------------
void writeBetweennessOutput(const std::string &filename,
                            const BetweennessResult &result)
{
    std::ofstream fout(filename);
    if (!fout.is_open())
        throw std::runtime_error("Unable to create output file.");

    fout << "Algorithm: Betweenness Centrality\n";
    fout << "Vertex Centrality\n";

    fout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < result.centrality.size(); ++i)
        fout << i << " " << result.centrality[i] << "\n";
}

//------------------------------------------------------
// Connected Components Output
//------------------------------------------------------
void writeComponentsOutput(const std::string &filename,
                           const ComponentsResult &result)
{
    std::ofstream fout(filename);
    if (!fout.is_open())
        throw std::runtime_error("Unable to create output file.");

    fout << "Algorithm: Connected Components\n";
    fout << "Number of components: " << result.count << "\n";
    fout << "Vertex Component\n";

    for (size_t i = 0; i < result.component.size(); ++i)
        fout << i << " " << result.component[i] << "\n";
}
