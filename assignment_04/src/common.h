#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

struct KMeansResult {
    std::vector<int> assignments;
    std::vector<std::vector<double>> centroids;
    double wcss = 0.0;
    int iterations = 0;
    bool converged = false;
};

KMeansResult kmeans(const std::vector<std::vector<double>>& points,
                    int k, double tolerance, int maxIterations);

struct FastMapResult {
    std::vector<std::vector<double>> coordinates;
    std::vector<std::pair<int, int>> pivots;
};

FastMapResult fastMap(std::vector<std::vector<double>>& distances,
                      int targetDimensions);

#endif
