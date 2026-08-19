#ifndef RUNNER_H
#define RUNNER_H

#include <functional>
#include <string>

#include "graph.h"

void runAlgorithm(
    const std::string &algorithmName,
    function<double(const CSRGraph &, int, const string &)> executor,
    bool weighted = false);




#endif
void runTriangleCounting();
void runBetweennessCentrality();
void runConnectedComponents();
