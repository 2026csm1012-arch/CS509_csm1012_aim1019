
#include "../src/common.h"

#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

bool readGD(const string& fileName, int& degree, vector<double>& c,
            double& x, double& rate, double& tolerance, int& maxIterations) {
    ifstream file(fileName);

    if (!file) {
        cout << "Error: Cannot open input file: " << fileName << endl;
        return false;
    }

    string word;

    file >> word >> degree;

    file >> word;
    c.resize(degree + 1);
    for (double& value : c)
        file >> value;

    file >> word >> x;
    file >> word >> rate;
    file >> word >> tolerance;
    file >> word >> maxIterations;

    return true;
}

string gdFile(int test) {
    return "tests/gradient_descent/gd_0" + to_string(test) + ".txt";
}

string flowFile(int test) {
    return "tests/maxflow/maxflow_0" + to_string(test) + ".txt";
}

double expectedGD(int test) {
    ifstream file("outputs/gradient_descent/gd_0" +
                  to_string(test) + ".txt");

    string word;
    double value;

    file >> word >> word >> value;
    return value;
}

long long expectedFlow(int test) {
    ifstream file("outputs/maxflow/maxflow_0" +
                  to_string(test) + ".txt");

    string word;
    long long value;

    file >> word >> word >> value;
    return value;
}

int main() {
    cout << fixed << setprecision(10);

    while (true) {
        cout << "\n=============================================\n";
        cout << " Assignment 03 - Buddy Task\n";
        cout << "=============================================\n";
        cout << "1. Gradient Descent\n";
        cout << "2. Maxflow-Mincut\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 0)
            break;

        if (choice != 1 && choice != 2) {
            cout << "Invalid choice.\n";
            continue;
        }

        cout << "\nTest cases:\n";

        if (choice == 1) {
            cout << "1. gd_01.txt (degree = 2)\n";
            cout << "2. gd_02.txt (degree = 4)\n";
            cout << "3. gd_03.txt (degree = 6)\n";
            cout << "4. gd_04.txt (degree = 8)\n";
            cout << "5. gd_05.txt (degree = 10)\n";
        } else {
            cout << "1. maxflow_01.txt (V = 10)\n";
            cout << "2. maxflow_02.txt (V = 100)\n";
            cout << "3. maxflow_03.txt (V = 1000)\n";
            cout << "4. maxflow_04.txt (V = 10000)\n";
            cout << "5. maxflow_05.txt (V = 50000)\n";
        }

        cout << "Enter test case: ";

        int test;
        cin >> test;

        if (test < 1 || test > 5) {
            cout << "Invalid test case.\n";
            continue;
        }

        if (choice == 1) {
            int degree, maxIterations;
            vector<double> c;
            double x, rate, tolerance;

            if (!readGD(gdFile(test), degree, c, x, rate,
                        tolerance, maxIterations))
                continue;

            auto start = chrono::high_resolution_clock::now();

            GDResult result = gradientDescent(
                c, x, rate, tolerance, maxIterations);

            auto end = chrono::high_resolution_clock::now();

            double time =
                chrono::duration<double, milli>(end - start).count();

            cout << "\nAlgorithm: Gradient Descent\n";
            cout << "Degree: " << result.degree << "\n";
            cout << "Final x: " << result.x << "\n";
            cout << "Final f(x): " << result.fx << "\n";
            cout << "Iterations: " << result.iterations << "\n";
            cout << "Converged: "
                 << (result.converged ? "true" : "false") << "\n";
            cout << "Execution time: " << time << " ms\n";

            double expected = expectedGD(test);
            cout << "Expected x*: " << expected << "\n";

            if (fabs(result.x - expected) < 1e-4)
                cout << "Validation: PASS\n";
            else
                cout << "Validation: FAIL\n";
        }

        else {
            Graph graph;

            if (!readMaxflowGraph(flowFile(test), graph))
                continue;

            auto start = chrono::high_resolution_clock::now();

            FlowResult result = maxflow(graph);

            auto end = chrono::high_resolution_clock::now();

            double time =
                chrono::duration<double, milli>(end - start).count();

            cout << "\nAlgorithm: Maxflow-Mincut\n";
            cout << "Source: " << graph.source << "\n";
            cout << "Sink: " << graph.sink << "\n";
            cout << "Maximum flow: " << result.maxFlow << "\n";
            cout << "Minimum cut capacity: " << result.minCut << "\n";

            cout << "Source side: ";
            for (int v : result.sourceSide)
                cout << v << " ";
            cout << "\n";

            cout << "Sink side: ";
            for (int v : result.sinkSide)
                cout << v << " ";
            cout << "\n";

            cout << "Cut edges:\n";
            for (auto e : result.cutEdges)
                cout << e.u << " " << e.v << " " << e.capacity << "\n";

            cout << "Execution time: " << time << " ms\n";

            long long expected = expectedFlow(test);
            cout << "Expected maximum flow: " << expected << "\n";

            if (result.maxFlow == expected &&
                result.maxFlow == result.minCut)
                cout << "Validation: PASS\n";
            else
                cout << "Validation: FAIL\n";
        }

        cout << "\nTest finished. Returning to menu...\n";
    }

    return 0;
}
