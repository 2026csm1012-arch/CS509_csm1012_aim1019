#include "../src/common.h"

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>

#include<vector>
#include <string>

using namespace std;

static bool readKMeans(const string& fileName,
                       vector<vector<double>>& points,
                       int& k, double& tolerance, int& maxIterations) {
    ifstream file(fileName);
    if (!file) {
        cout << "Error: Cannot open input file: " << fileName << '\n';
        return false;
    }

    int n, d;
    if (!(file >> n >> d >> k) || n <= 0 || d <= 0 || k <= 0 || k > n) {
        cout << "Error: Invalid N, D or K.\n";
        return false;
    }

    points.assign(n, vector<double>(d));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < d; ++j) {
            if (!(file >> points[i][j])) {
                cout << "Error: Invalid point data.\n";
                return false;
            }
        }
    }

    string word;
    if (!(file >> word >> maxIterations) || word != "MAX_ITERATIONS" ||
        maxIterations <= 0) {
        cout << "Error: Invalid MAX_ITERATIONS.\n";
        return false;
    }

    if (!(file >> word >> tolerance) || word != "TOLERANCE" ||
        tolerance <= 0.0) {
        cout << "Error: Invalid TOLERANCE.\n";
        return false;
    }

    return true;
}

static bool readFastMap(const string& fileName,
                        vector<vector<double>>& distances, int& k) {
    ifstream file(fileName);
    if (!file) {
        cout << "Error: Cannot open input file: " << fileName << '\n';
        return false;
    }

    int n;
    if (!(file >> n >> k) || n <= 0 || k <= 0 || k >= n) {
        cout << "Error: Invalid N or target dimensionality k.\n";
        return false;
    }

    distances.assign(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(file >> distances[i][j])) {
                cout << "Error: Invalid distance matrix.\n";
                return false;
            }
            if (distances[i][j] < 0.0) {
                cout << "Error: Negative distance.\n";
                return false;
            }
        }
    }

    const double eps = 1e-9;
    for (int i = 0; i < n; ++i) {
        if (fabs(distances[i][i]) > eps) {
            cout << "Error: Distance matrix has non-zero diagonal.\n";
            return false;
        }
        for (int j = i + 1; j < n; ++j) {
            if (fabs(distances[i][j] - distances[j][i]) > eps) {
                cout << "Error: Distance matrix is not symmetric.\n";
                return false;
            }
        }
    }

    return true;
}

static string kmFile(int test) {
    return "tests/kmeans/km_0" + to_string(test) + ".txt";
}

static string fmFile(int test) {
    return "tests/fastmap/fm_0" + to_string(test) + ".txt";
}

static void runKMeans(int test) {
    vector<vector<double>> points;
    int k, maxIterations;
    double tolerance;

    if (!readKMeans(kmFile(test), points, k, tolerance, maxIterations))
        return;

    auto start = chrono::high_resolution_clock::now();
    KMeansResult result = kmeans(points, k, tolerance, maxIterations);
    auto end = chrono::high_resolution_clock::now();

    double time = chrono::duration<double, milli>(end - start).count();

    cout << "\nAlgorithm: K-Means Clustering\n";
    cout << "N: " << points.size() << '\n';
    cout << "D: " << points[0].size() << '\n';
    cout << "K: " << k << '\n';

//    cout << "Point assignments:\n";
//    for (size_t i = 0; i < result.assignments.size(); ++i)
//        cout << i << ' ' << result.assignments[i] << '\n';
//
    cout << "Final centroids:\n";
    for (int c = 0; c < k; ++c) {
        cout << c << ":";
        for (double x : result.centroids[c])
            cout << ' ' << x;
        cout << '\n';
    }

    cout << "WCSS: " << result.wcss << '\n';
    cout << "Iterations: " << result.iterations << '\n';
    cout << "Converged: " << (result.converged ? "true" : "false") << '\n';
    cout << "Execution time: " << time << " ms\n";
}

static void runFastMap(int test) {
    vector<vector<double>> distances;
    int k;

    if (!readFastMap(fmFile(test), distances, k))
        return;

    auto start = chrono::high_resolution_clock::now();
    FastMapResult result = fastMap(distances, k);
    auto end = chrono::high_resolution_clock::now();

    double time = chrono::duration<double, milli>(end - start).count();

    cout << "\nAlgorithm: FastMap\n";
    cout << "N: " << distances.size() << '\n';
    cout << "Target dimensions: " << k << '\n';

    cout << "Pivots per dimension:\n";
    for (size_t d = 0; d < result.pivots.size(); ++d)
        cout << "Dim " << d + 1 << ": "
             << result.pivots[d].first << ' '
             << result.pivots[d].second << '\n';

    cout << "Object coordinates:\n";
    cout << setprecision(10);
    for (size_t i = 0; i < result.coordinates.size(); ++i) {
        cout << i << ":";
        for (double x : result.coordinates[i])
            cout << ' ' << x;
        cout << '\n';
    }

    cout << "Execution time: " << time << " ms\n";
}

int main() {
    cout << fixed << setprecision(6);

    while (true) {
        cout << "\n=============================================\n";
        cout << " Assignment 04 - Buddy Task\n";
        cout << "=============================================\n";
        cout << "1. K-Means Clustering\n";
        cout << "2. FastMap\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        int choice;
        if (!(cin >> choice))
            return 0;

        if (choice == 0)
            break;

        if (choice != 1 && choice != 2) {
            cout << "Invalid choice.\n";
            continue;
        }

        cout << "\nTest cases:\n";
        if (choice == 1) {
            cout << "1. km_01.txt (N=100, D=2, K=3)\n";
            cout << "2. km_02.txt (N=1000, D=2, K=5)\n";
            cout << "3. km_03.txt (N=10000, D=5, K=8)\n";
            cout << "4. km_04.txt (N=100000, D=5, K=10)\n";
        } else {
            cout << "1. fm_01.txt (N=10, k=2)\n";
            cout << "2. fm_02.txt (N=100, k=2)\n";
            cout << "3. fm_03.txt (N=1000, k=3)\n";
       }

        cout << "Enter test case: ";
        int test;
        cin >> test;

        if (test < 1 || test > 4) {
            cout << "Invalid test case.\n";
            continue;
        }

        if (choice == 1)
            runKMeans(test);
        else
            runFastMap(test);

        cout << "\nTest finished. Returning to menu...\n";
    }

    return 0;
}
