#include "fastmap.h"

#include<vector>
#include <cmath>
using namespace std;

static int farthestFrom(const vector<vector<double>>& d,
                        int source) {
    int farthest = source;
    double best = -1.0;

    for (int i = 0; i < static_cast<int>(d.size()); ++i) {
        if (d[source][i] > best) {
            best = d[source][i];
            farthest = i;
        }
    }
    return farthest;
}

FastMapResult fastMap(vector<vector<double>>& distances,
                      int targetDimensions) {
    const int n = static_cast<int>(distances.size());

    FastMapResult result;
    result.coordinates.assign(
        n, vector<double>(targetDimensions, 0.0));

    // Deflate the input distance matrix in-place. This avoids an unnecessary
    // second NxN matrix and is important for the larger required test.
    for (int dim = 0; dim < targetDimensions; ++dim) {
        // Pivot heuristic: choose an object, find its farthest object,
        // then find the object farthest from that pivot.
        int a = farthestFrom(distances, 0);
        int b = farthestFrom(distances, a);

        result.pivots.push_back({a, b});

        const double dab = distances[a][b];
        if (dab <= 0.0)
            break;

        const double dab2 = dab * dab;

        // Projection using the law of cosines.
        for (int i = 0; i < n; ++i) {
            const double dai2 = distances[a][i] * distances[a][i];
            const double dbi2 = distances[b][i] * distances[b][i];

            double numerator = dai2 + dab2 - dbi2;
            result.coordinates[i][dim] =
                numerator / (2.0 * dab);
        }

        // Deflate the remaining distances:
        // d'(i,j)^2 = d(i,j)^2 - (x_i - x_j)^2.
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                double d2 = distances[i][j] * distances[i][j];
                double delta = result.coordinates[i][dim] -
                               result.coordinates[j][dim];

                double residual2 = d2 - delta * delta;
                distances[i][j] =
                    residual2 > 0.0 ? sqrt(residual2) : 0.0;
            }
        }
    }

    return result;
}
