#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include "graph.h"

//------------------------------------------
// BFS Output
//------------------------------------------
void writeBFSOutput(const std::string &filename,
                    const BFSResult &result,
                    int source);

//------------------------------------------
// DFS Output
//------------------------------------------
void writeDFSOutput(const std::string &filename,
                    const DFSResult &result,
                    int source);

//------------------------------------------
// SSSP Output
//------------------------------------------
void writeSSSPOutput(const std::string &filename,
                    const SSSPResult &result,
                    int source);

#endif
void writeBellmanFordOutput(const std::string &filename,
                            const BellmanFordResult &result,
                            int source);
void writeFloydWarshallOutput(const std::string &filename,
                              const FloydWarshallResult &result);
void writeTriangleOutput(const std::string &filename,
                         const TriangleResult &result);
void writeBetweennessOutput(const std::string &filename,
                            const BetweennessResult &result);
void writeComponentsOutput(const std::string &filename,
                           const ComponentsResult &result);
