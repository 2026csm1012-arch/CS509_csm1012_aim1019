#include "kmeans.h"

#include <cmath>
#include<vector>
#include <limits>

using namespace std;

static double squaredDistance(const vector<double>& a,
                              const vector<double>& b) {
    double sum = 0.0;
    for (size_t j = 0; j < a.size(); ++j) {
        double diff = a[j] - b[j];
        sum += diff * diff;
    }
    return sum;
}

KMeansResult kmeans(const vector<vector<double>>& points,
                    int k, double tolerance, int maxIterations) {
    KMeansResult result;
    const int n = static_cast<int>(points.size());
    const int d = static_cast<int>(points[0].size());

    result.assignments.assign(n, -1);
    result.centroids.assign(k, vector<double>(d, 0.0));

    // Recommended deterministic initialization: first K input points.
    for (int c = 0; c < k; ++c)
        result.centroids[c] = points[c];

    for (int iteration = 1; iteration <= maxIterations; ++iteration) {
        bool changed = false;

        // Assignment step.
        for (int i = 0; i < n; ++i) {
            int best = 0;
            double bestDistance = squaredDistance(points[i], result.centroids[0]);

            for (int c = 1; c < k; ++c) {
                double dist = squaredDistance(points[i], result.centroids[c]);
                if (dist < bestDistance) {
                    bestDistance = dist;
                    best = c;
                }
            }

            if (result.assignments[i] != best) {
                result.assignments[i] = best;
                changed = true;
            }
        }

        // Update step.
        vector<vector<double>> sums( k, vector<double>(d, 0.0));
        vector<int> counts(k, 0);

        for (int i = 0; i < n; ++i) {
            int c = result.assignments[i];
            ++counts[c];
            for (int j = 0; j < d; ++j)
                sums[c][j] += points[i][j];
        }

        double maxShift = 0.0;
        for (int c = 0; c < k; ++c) {
            // Required behavior for an empty cluster: keep old centroid.
            if (counts[c] == 0)
                continue;

            vector<double> newCentroid(d);
            for (int j = 0; j < d; ++j)
                newCentroid[j] = sums[c][j] / counts[c];

            double shift = sqrt( squaredDistance(result.centroids[c], newCentroid));
            if (shift > maxShift)
                maxShift = shift;

            result.centroids[c] = move(newCentroid);
        }

        result.iterations = iteration;

        if (!changed || maxShift <= tolerance) {
            result.converged = true;
            break;
        }
    }

    // WCSS is evaluated using the final assignments and final centroids.
    result.wcss = 0.0;
    for (int i = 0; i < n; ++i)
        result.wcss += squaredDistance(points[i], result.centroids[result.assignments[i]]);

    return result;
}
