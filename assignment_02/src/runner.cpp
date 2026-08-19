#include "runner.h"

#include <iostream>
#include <iomanip>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>

#include "graph.h"
#include "graph_io.h"
#include "csr.h"
#include "timer.h"
#include "output.h"
#include "compare.h"
#include "triangle.h"
#include "betweenness.h"
#include "components.h"

using namespace std;
namespace fs = std::filesystem;

//---------------------------------------------------------
// Get all .txt test files from a folder
//---------------------------------------------------------
vector<fs::path> getTestFiles(const string &folder)
{
    vector<fs::path> files;

    if (!fs::exists(folder))
    {
        throw runtime_error("Tests directory not found: " + folder);
    }

    for (const auto &entry : fs::directory_iterator(folder))
    {
        if (entry.path().extension() == ".txt")
        {
            files.push_back(entry.path());
        }
    }

    sort(files.begin(), files.end());

    return files;
}

//---------------------------------------------------------
// Create generated output directory
//---------------------------------------------------------
void createGeneratedDirectory(const string &folder)
{
    if (!fs::exists(folder))
    {
        fs::create_directories(folder);
    }
}

void printHeader(const string &algorithm)
{
    cout << "=========================================\n";
    cout << "   " << algorithm << " Automatic Test Runner\n";
    cout << "=========================================\n\n";

    cout << left
         << setw(20) << "Test File"
         << setw(10) << "Status"
         << "Execution Time\n";

    cout << "----------------------------------------------------------\n";
}

void printSummary(int passed, int failed)
{
    cout << "\n=========================================\n";

    cout << "Total Tests : "
         << passed + failed
         << '\n';

    cout << "Passed      : "
         << passed
         << '\n';

    cout << "Failed      : "
         << failed
         << '\n';

    cout << "=========================================\n";
}

void runAlgorithm(
    const string &algorithmName,
    function<double(const CSRGraph &, int, const string &)> executor,
    bool weighted)
{
    string testFolder =
        "tests/" + algorithmName;

    string outputFolder =
        "outputs/" + algorithmName;

    string generatedFolder =
        "generated/" + algorithmName;

    createGeneratedDirectory(generatedFolder);

    vector<fs::path> testFiles =
        getTestFiles(testFolder);

    if (testFiles.empty())
    {
        cout << "No test files found.\n";
        return;
    }

    int passed = 0;
    int failed = 0;

    string title = algorithmName;

    transform(title.begin(),
              title.end(),
              title.begin(),
              ::toupper);

    printHeader(title);

    for (const auto &testFile : testFiles)
    {
        Graph graph =
            readGraph(testFile.string(), weighted);

        // CSR conversion is preprocessing: it happens here, before the
        // executor (and its internal Timer) ever starts, so its cost is
        // never counted as part of the algorithm's reported runtime.
        CSRGraph csr =
            convertToCSR(graph);

        string filename =
            testFile.filename().string();

        string generatedFile =
            generatedFolder + "/" + filename;

        string expectedFile =
            outputFolder + "/" + filename;

        double executionTime =
            executor(
                csr,
                graph.source,
                generatedFile);

        bool ok =
            compareFiles(
                expectedFile,
                generatedFile);

        cout
            << left
            << setw(20)
            << filename;

        if (ok)
        {
            passed++;

            cout
                << setw(10)
                << "PASS";
        }
        else
        {
            failed++;

            cout
                << setw(10)
                << "FAIL";
        }

        cout << fixed
             << setprecision(3)
             << executionTime
             << " ms\n";
    }

    printSummary(
        passed,
        failed);
}

//---------------------------------------------------------
// Generic runner for global (no SOURCE) algorithms
//---------------------------------------------------------
void runGlobalAlgorithm(
    const string &algorithmName,
    function<double(const CSRGraph &, const string &)> executor)
{
    string testFolder = "tests/" + algorithmName;
    string outputFolder = "outputs/" + algorithmName;
    string generatedFolder = "generated/" + algorithmName;

    createGeneratedDirectory(generatedFolder);
    vector<fs::path> testFiles = getTestFiles(testFolder);

    if (testFiles.empty())
    {
        cout << "No test files found.\n";
        return;
    }

    int passed = 0;
    int failed = 0;
    string title = algorithmName;

    transform(title.begin(), title.end(), title.begin(), ::toupper);
    printHeader(title);

    for (const auto &testFile : testFiles)
    {
        Graph graph = readGraph(testFile.string(), false);
        CSRGraph csr = convertToCSR(graph);

        string filename = testFile.filename().string();
        string generatedFile = generatedFolder + "/" + filename;
        string expectedFile = outputFolder + "/" + filename;

        double executionTime = executor(csr, generatedFile);
        bool ok = compareFiles(expectedFile, generatedFile);

        cout << left << setw(20) << filename
             << setw(10) << (ok ? "PASS" : "FAIL")
             << fixed << setprecision(3)
             << executionTime << " ms\n";

        if (ok) ++passed;
        else ++failed;
    }

    printSummary(passed, failed);
}

//---------------------------------------------------------
// Triangle Counting Test Suite
//---------------------------------------------------------
void runTriangleCounting()
{
    runGlobalAlgorithm(
        "triangle",
        [](const CSRGraph &csr,
           const string &generatedFile) -> double
        {
            Timer timer;
            timer.start();

            TriangleResult result =
                triangleCounting(csr);

            timer.stop();

            writeTriangleOutput(
                generatedFile, result);

            return timer.elapsedMilliseconds();
        });
}

//---------------------------------------------------------
// Betweenness Centrality Test Suite
//---------------------------------------------------------
void runBetweennessCentrality()
{
    runGlobalAlgorithm(
        "betweenness",
        [](const CSRGraph &csr,
           const string &generatedFile) -> double
        {
            Timer timer;
            timer.start();

            BetweennessResult result =
                betweennessCentrality(csr);

            timer.stop();

            writeBetweennessOutput(
                generatedFile, result);

            return timer.elapsedMilliseconds();
        });
}

//---------------------------------------------------------
// Connected Components Test Suite
//---------------------------------------------------------
void runConnectedComponents()
{
    runGlobalAlgorithm(
        "components",
        [](const CSRGraph &csr,
           const string &generatedFile) -> double
        {
            Timer timer;
            timer.start();

            ComponentsResult result =
                connectedComponents(csr);

            timer.stop();

            writeComponentsOutput(
                generatedFile, result);

            return timer.elapsedMilliseconds();
        });
}
