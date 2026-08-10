#include "output.h"

#include <fstream>
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