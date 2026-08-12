# CS509_csm1012_aim1019
Assignment 02 – Graph Algorithms

C++17 implementation of graph algorithms using an adjacency-list input layer and a shared Compressed Sparse Row (CSR) representation.

Assignment 02 Algorithms

The repository contains implementations for:

Bellman-Ford

Floyd-Warshall

Triangle Counting

Betweenness Centrality

Connected Components

The project also retains BFS, DFS and SSSP modules from the earlier graph-algorithm work. They are available through the same test runner.

1. Project Structure

assignment_02/
│
├── driver/
│   └── main.cpp
│
├── src/
│   ├── graph.h
│   ├── graph_io.h
│   ├── graph_io.cpp
│   ├── csr.h
│   ├── csr.cpp
│   ├── runner.h
│   ├── runner.cpp
│   ├── timer.h
│   ├── compare.h
│   ├── compare.cpp
│   │
│   ├── bfs.h / bfs.cpp
│   ├── dfs.h / dfs.cpp
│   ├── sssp.h / sssp.cpp
│   │
│   ├── bellman_ford.h / bellman_ford.cpp
│   ├── floyd_warshall.h / floyd_warshall.cpp
│   ├── triangle.h / triangle.cpp
│   ├── betweenness.h / betweenness.cpp
│   ├── components.h / components.cpp
│   │
│   └── output.h / output.cpp
│
├── tests/
│   ├── bellman_ford/
│   ├── floyd_warshall/
│   ├── triangle/
│   ├── betweenness/
│   ├── components/
│   ├── bfs/
│   ├── dfs/
│   └── sssp/
│
├── outputs/
│   ├── bellman_ford/
│   ├── floyd_warshall/
│   ├── triangle/
│   ├── betweenness/
│   ├── components/
│   ├── bfs/
│   ├── dfs/
│   └── sssp/
│
├── generated/
│   └── <algorithm>/
│
├── Makefile
└── README.md

2. Architecture

The implementation follows this pipeline:

Input test file
      │
      ▼
Graph reader
      │
      ▼
Adjacency-list Graph
      │
      ▼
convertToCSR()
      │
      ▼
CSRGraph
      │
      ▼
Selected algorithm
      │
      ▼
Algorithm result
      │
      ▼
Output writer
      │
      ▼
generated/<algorithm>/test_XX.txt
      │
      ▼
Compare with outputs/<algorithm>/test_XX.txt
      │
      ▼
PASS / FAIL

CSR conversion is performed before the algorithm timer starts, so preprocessing is not included in the reported algorithm execution time.

3. Shared CSR Representation

CSRGraph contains:

V – number of vertices

E – number of edges

source – source vertex where applicable

weighted – whether edge weights are present

row_ptr – CSR row offsets

col_idx – destination vertices

weights – parallel edge-weight array for weighted graphs

The same CSR structure is shared by the graph algorithms.

4. Input Format

The repository's graph reader expects:

V E
vertex degree neighbour ...
vertex degree neighbour ...
...
SOURCE source

For weighted graphs:

V E
vertex degree neighbour weight neighbour weight ...
...
SOURCE source

For algorithms without a source, the graph files do not require a SOURCE line.

The current repository uses this adjacency-list representation for Bellman-Ford and Floyd-Warshall. Floyd-Warshall first constructs a distance matrix from the CSR graph before the Floyd-Warshall kernel is timed.

5. Algorithms

5.1 Bellman-Ford

Implementation:

src/bellman_ford.cpp
src/bellman_ford.h

Flow:

Weighted graph
     ↓
CSR
     ↓
Initialize source distance = 0
     ↓
V-1 relaxation passes
     ↓
Negative-cycle check
     ↓
Shortest-path distances

The implementation stops early if a relaxation pass produces no changes.

Time complexity:

O(VE)

5.2 Floyd-Warshall

Implementation:

src/floyd_warshall.cpp
src/floyd_warshall.h

Flow:

CSR graph
   ↓
Build V × V distance matrix
   ↓
Floyd-Warshall triple loop
   ↓
Check diagonal for negative cycle
   ↓
All-pairs shortest-path matrix

Time complexity:

O(V³)

The matrix construction is performed before the timer starts.

5.3 Triangle Counting

Implementation:

src/triangle.cpp
src/triangle.h

The implementation counts triangles using CSR adjacency and vertex ordering. It also records the discovered triangle triples.

Example output:

Algorithm: Triangle Counting

Total triangles: 3
Triangles found:
(0, 1, 2)
(1, 2, 3)
(3, 4, 5)

5.4 Betweenness Centrality

Implementation:

src/betweenness.cpp
src/betweenness.h

The implementation performs a BFS-based shortest-path accumulation for every source vertex and calculates a centrality value for each vertex.

Time complexity of the implemented unweighted Brandes-style approach is approximately:

O(V(V + E))

for an adjacency-list graph.

5.5 Connected Components

Implementation:

src/components.cpp
src/components.h

The implementation performs BFS from every previously unvisited vertex and assigns a component ID.

Time complexity:

O(V + E)

for the CSR graph.

6. Driver

The entry point is:

driver/main.cpp

The menu provides:

1. Breadth First Search (BFS)
2. Depth First Search (DFS)
3. Single Source Shortest Path (SSSP)
4. Bellman-Ford
5. Floyd-Warshall
6. Triangle Counting
7. Betweenness Centrality
8. Connected Components
0. Exit

Selecting an algorithm automatically runs every .txt file in its corresponding tests/<algorithm>/ directory.

7. Output and Validation

For each test:

Input is read.

The graph is converted to CSR.

The algorithm is executed.

Only the algorithm execution is timed.

The generated result is written to generated/<algorithm>/.

The generated file is compared with outputs/<algorithm>/.

PASS or FAIL is printed.

The comparison is currently performed by src/compare.cpp using exact line-by-line string comparison.

8. Test Inventory in the Submitted Archive

Algorithm

Test Cases

Bellman-Ford

4

Floyd-Warshall

4

Triangle Counting

6

Betweenness Centrality

6

Connected Components

6

BFS

8

DFS

8

SSSP

4

The five core Assignment 02 algorithms therefore currently contain 26 test files.

9. Expected Results Present in the Archive

Bellman-Ford

Test

Vertices

Edges

Source

Expected Result

test_01

5

6

0

0, 3, 1, 4, 7

test_02

6

5

0

0, 2, 4, 5, INF, INF

test_03

1

0

0

0

test_04

4

4

0

0, 2, 5, 9

Floyd-Warshall

Test

Vertices

Edges

Expected Result

test_01

5

6

5 × 5 distance matrix

test_02

6

5

6 × 6 distance matrix

test_03

1

0

1 × 1 matrix

test_04

4

4

4 × 4 distance matrix

Triangle Counting

Test

Vertices

Edges

Expected Triangles

test_01

6

8

3

test_02

3

3

1

test_03

4

6

4

test_04

10

15

2

test_05

15

15

5

test_06

30

30

10

Betweenness Centrality

The archive contains one genuine Betweenness Centrality expected output for test_01:

0 0.00
1 3.00
2 4.00
3 3.00
4 0.00

The expected-output files test_02 through test_06 currently contain Triangle Counting output, not Betweenness Centrality output.

Connected Components

The archive contains one genuine Connected Components expected output for test_01:

Number of components: 4
Vertex Component
0 0
1 0
2 0
3 0
4 1
5 1
6 2
7 3

The expected-output files test_02 through test_06 currently contain Triangle Counting output, not Connected Components output.

10. Current Validation of the Submitted Archive

The project was compiled from the submitted archive using:

make clean
make

Compilation completed successfully with:

g++ -std=c++17 -Wall -Wextra -O2

The source code therefore builds successfully.

However, the current compareFiles() implementation performs exact string comparison. The expected files in the archive use CRLF line endings while generated files use LF line endings in a Linux build. As a result, the validation run reports differences such as:

Difference at line 1
Expected : Algorithm: Bellman-Ford\r
Generated: Algorithm: Bellman-Ford

This is a line-ending mismatch rather than an algorithm-result mismatch.

There is also a separate test-fixture problem:

outputs/betweenness/test_02.txt ... test_06.txt
outputs/components/test_02.txt ... test_06.txt

contain Triangle Counting output. These files do not match the corresponding algorithm's output format.

Therefore, the current archive should not be described as having all tests passing until the line-ending comparison and incorrect expected fixtures are corrected.

11. Build and Run

From the assignment_02 directory:

make clean
make

Run:

./graph_runner

On Windows with MinGW:

mingw32-make clean
mingw32-make
.\graph_runner.exe

Then select the required algorithm from the menu.

12. Required Fixes Before Final Submission

Fix 1 – Normalize line endings

The comparison should normalize CRLF/LF or strip a trailing \r before comparing lines.

This prevents valid output from being marked FAIL only because of Windows/Linux line endings.

Fix 2 – Correct Betweenness expected files

Create genuine expected outputs for:

outputs/betweenness/test_02.txt
outputs/betweenness/test_03.txt
outputs/betweenness/test_04.txt
outputs/betweenness/test_05.txt
outputs/betweenness/test_06.txt

Fix 3 – Correct Connected Components expected files

Create genuine expected outputs for:

outputs/components/test_02.txt
outputs/components/test_03.txt
outputs/components/test_04.txt
outputs/components/test_05.txt
outputs/components/test_06.txt

Fix 4 – Verify test naming against the assignment specification

The submitted archive uses:

test_01.txt
test_02.txt
...

for the core Assignment 02 algorithms.

If the final assignment specification requires names such as:

bf_10.txt
fw_10.txt
tc_10.txt
bc_10.txt
cc_10.txt

the repository should be renamed/regenerated accordingly before submission.

13. Development Plan

Phase

Work

Phase 1

Establish shared Graph and CSR representation

Phase 2

Implement/reuse BFS, DFS and SSSP infrastructure

Phase 3

Implement Bellman-Ford with negative-cycle detection

Phase 4

Implement Floyd-Warshall and distance-matrix generation

Phase 5

Implement Triangle Counting

Phase 6

Implement Betweenness Centrality

Phase 7

Implement Connected Components

Phase 8

Integrate all algorithms into the common runner

Phase 9

Add output generation and expected-output comparison

Phase 10

Measure algorithm-only execution time

Phase 11

Correct test fixtures and normalize line endings

Phase 12

Final verification and README/result-table preparation

14. Final Status

Area

Status

C++17 build

Working

Shared CSR representation

Implemented

Common driver/menu

Implemented

Bellman-Ford

Implemented

Floyd-Warshall

Implemented

Triangle Counting

Implemented

Betweenness Centrality

Implemented

Connected Components

Implemented

Algorithm-only timer placement

Implemented

Output generation

Implemented

Automatic test discovery

Implemented

Exact output comparison

Implemented, but currently line-ending sensitive

Betweenness expected fixtures

Needs correction

Connected Components expected fixtures

Needs correction

Final assignment result tables

To be completed after fixture correction

Conclusion

The submitted Assignment 02 archive contains a complete multi-algorithm graph-processing framework built around a shared CSR representation. The core Assignment 02 algorithms—Bellman-Ford, Floyd-Warshall, Triangle Counting, Betweenness Centrality and Connected Components—are implemented and connected to a common automated runner.

The build succeeds, but the current validation data needs cleanup before final submission. In particular, the comparison function is sensitive to CRLF/LF differences, and several Betweenness Centrality and Connected Components expected files currently contain Triangle Counting results. These are repository/test-data issues that should be resolved before recording final PASS/FAIL results.
