#include "output.h"

#include <fstream>
#include <iomanip>
#include <stdexcept>


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
