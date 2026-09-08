#ifndef KMEANS_H
#define KMEANS_H

#include "common.h"
KMeansResult kmeans(const std::vector<std::vector<double>>& points,
                    int k, double tolerance, int maxIterations);
#endif
