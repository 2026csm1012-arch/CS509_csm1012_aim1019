#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include "graph.h"

void writeTriangleOutput(const std::string &filename,
                         const TriangleResult &result);
void writeBetweennessOutput(const std::string &filename,
                            const BetweennessResult &result);
void writeComponentsOutput(const std::string &filename,
                           const ComponentsResult &result);
                           
                           
#endif
