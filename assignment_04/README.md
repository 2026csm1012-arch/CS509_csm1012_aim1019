# CS509 - Assignment 04 - Buddy Task

This folder contains **Assignment 04 - Buddy Task** for CS509.

The assignment is implemented as a **pair task for two students** and contains only the two buddy algorithms specified in the assignment:

1. **K-Means Clustering**
2. **FastMap**
 

---

## 1. Assignment Structure

| Task Type  | Algorithms                     | Work Mode            |
| ---------- | ------------------------------ | -------------------- |
| Buddy Task | K-Means Clustering and FastMap | Pair of two students |

### Candidate Names

* **Deepak Kumar** 2026CSM1012
* **Rajan Jha** 2026AIM1019
 
# 2. Algorithms

## 2.1 K-Means Clustering

K-Means Clustering partitions **N data points in D-dimensional space into K clusters**. Each point is assigned to the cluster whose centroid is closest to it.

The algorithm minimizes the **Within-Cluster Sum of Squares (WCSS)**.

### Working

1. Initialize K centroids using the first K input points.
2. Calculate the distance from every point to every centroid.
3. Assign each point to the nearest centroid.
4. Recalculate each centroid as the mean of all points assigned to it.
5. Repeat the assignment and update steps.
6. Stop when the centroid movement is below the specified tolerance or the maximum number of iterations is reached.
7. If a cluster becomes empty, its previous centroid is retained.

### Input

```text
N D K

point_0
point_1
...
point_(N-1)

MAX_ITERATIONS n
TOLERANCE epsilon
```

### Output

The program reports:

* Cluster assignment of every point
* Final centroid of every cluster
* WCSS
* Number of iterations
* Convergence status
* Execution time

---

## 2.2 FastMap

FastMap maps objects described by pairwise distances into a lower-dimensional Euclidean space.

It produces coordinates without requiring eigen-decomposition.

### Working

1. Select two approximately farthest pivot objects.
2. Project every object onto the line joining the two pivots.
3. Store the resulting coordinate.
4. Deflate the remaining distances by removing the contribution of the current dimension.
5. Repeat for every requested target dimension.

### Input

```text
N K

d(0,0) d(0,1) ... d(0,N-1)
d(1,0) d(1,1) ... d(1,N-1)
...
d(N-1,0) ... d(N-1,N-1)
```

### Output

The program reports:

* Target dimensionality
* Pivot objects selected for every dimension
* Coordinates of every object
* Execution time

---

# 3. Directory Structure

```text
assignment_04/
│
├── README.md
├── Makefile
│
├── src/
│   ├── kmeans.cpp
│   ├── kmeans.h
│   ├── fastmap.cpp
│   └── fastmap.h
│
├── driver/
│   └── main.cpp
│
├── tests/
│   ├── kmeans/
│   │   ├── km_01.txt
│   │   ├── km_02.txt
│   │   ├── km_03.txt
│   │   └── km_04.txt
│   │
│   └── fastmap/
│       ├── fm_01.txt
│       ├── fm_02.txt
│       ├── fm_03.txt
│       └── fm_04.txt
│
├── outputs/
│
└── tools/
    └── generate_fastmap.py
```

---

# 4. Required Test Cases

## 4.1 K-Means

| File        |       N |  D |  K |
| ----------- | ------: | -: | -: |
| `km_01.txt` |     100 |  2 |  3 |
| `km_02.txt` |   1,000 |  2 |  5 |
| `km_03.txt` |  10,000 |  5 |  8 |
| `km_04.txt` | 100,000 |  5 | 10 |

The same implementation must work for different values of **N, D and K**.

---

## 4.2 FastMap

| File        |      N | Target k |
| ----------- | -----: | -------: |
| `fm_01.txt` |     10 |        2 |
| `fm_02.txt` |    100 |        2 |
| `fm_03.txt` |  1,000 |        3 |
| `fm_04.txt` | 10,000 |        3 |

The same implementation must work for different values of **N and k**.

---

# 5. Compilation

From the `assignment_04` directory:

```bash
make
```

The project is compiled using C++17.

To remove compiled files:

```bash
make clean
```

---

# 6. Running the Program

The driver accepts the algorithm and input file.

### K-Means

```bash
./assignment_04_buddy kmeans tests/kmeans/km_01.txt
```

### FastMap

```bash
./assignment_04_buddy fastmap tests/fastmap/fm_01.txt
```

If the driver is implemented with an interactive menu, the corresponding algorithm and input file can be selected through the menu.

---

# 7. Timing Requirements

Only the **algorithm execution time** is measured.

The following operations are excluded from the reported algorithm time:

* File reading
* Input parsing
* Data preparation
* Output printing
* File writing
* Other setup operations

For K-Means, the timed section includes:

* Assignment step
* Centroid update
* All iterations

For FastMap, the timed section includes:

* Pivot selection
* Projection
* Distance deflation
* All target dimensions

Execution time is reported in milliseconds.

---

# 8. K-Means Results Table

| **File**  |   **N** | **D** | **K** | **Max Iter.** | **Actual Iter.** |      **WCSS** |    **Time** | **Status** |
| --------- | ------: | ----: | ----: | ------------: | ---------------: | ------------: | ----------: | ---------- |
| km_01.txt |     100 |     2 |     3 |           300 |                2 |     17.022449 | 0.003075 ms | Pass       |
| km_02.txt |   1,000 |     2 |     5 |           300 |                2 |    170.175385 | 0.018418 ms | Pass       |
| km_03.txt |  10,000 |     5 |     8 |           300 |                2 |  4,249.961070 | 0.535272 ms | Pass       |
| km_04.txt | 100,000 |     5 |    10 |           300 |                2 | 42,499.944581 | 7.025615 ms | Pass       |

---

# 9. FastMap Results Table

| **File**  |  **N** | **Target k** | **Pivots (per dim)**       | **Avg. Distance Error** |     **Time** | **Status** |
| --------- | -----: | -----------: | -------------------------- | ----------------------: | -----------: | ---------- |
| fm_01.txt |     10 |            2 | (9,0), (0,0)               |                     ... |  0.001192 ms | Pass       |
| fm_02.txt |    100 |            2 | (99,0), (9,90)             |                     ... |  0.094600 ms | Pass       |
| fm_03.txt |  1,000 |            3 | (999,0), (9,990), (93,905) |                     ... | 14.351375 ms | Pass       |
| fm_04.txt | 10,000 |            3 | ...                        |                     ... |          ... | Pending    |

> The average distance error is left as `...` until it is calculated from the generated coordinates. No unverified value is reported.

---

# 10. Test File Naming

### K-Means

```text
km_01.txt
km_02.txt
km_03.txt
km_04.txt
```

### FastMap

```text
fm_01.txt
fm_02.txt
fm_03.txt
fm_04.txt
```

---

# 11. Large FastMap Dataset

The `fm_04.txt` dataset contains a **10,000 × 10,000 distance matrix**, which is very large.

A generator is provided in:

```text
tools/generate_fastmap.py
```

It can be used to generate the required dataset rather than storing a huge generated matrix unnecessarily in the repository.

Example:

```bash
python3 tools/generate_fastmap.py 10000 3 tests/fastmap/fm_04.txt
```

After generation:

```bash
./assignment_04_buddy fastmap tests/fastmap/fm_04.txt
```

If the test does not complete because of memory limitations or excessive execution time, the observed result should be documented in the report.

---

# 12. Correctness

## K-Means

Correctness is checked using:

* Valid cluster assignment for every point
* Correct centroid calculation
* WCSS calculation
* Convergence condition
* Handling of empty clusters

## FastMap

Correctness is checked using:

* Valid pivot selection
* Correct coordinate projection
* Correct distance deflation
* Correct number of target dimensions
* Non-negative and valid distance calculations

---

# 13. Error Handling

The program should reject invalid K-Means input such as:

* Non-positive N
* Non-positive D
* Non-positive K
* K greater than N
* Non-positive tolerance
* Non-positive maximum iterations

For FastMap, the program should reject:

* Non-positive N
* Non-positive target dimensionality
* Target `k >= N`
* Non-square distance matrix
* Non-symmetric distance matrix
* Non-zero diagonal
* Negative distances

Invalid or missing input files should produce a clear error message.

---

# 14. Real-Life Applications

## K-Means

* Customer segmentation
* Image compression
* Document clustering
* Anomaly detection
* Feature engineering
* Data summarization

## FastMap

* Dimensionality reduction
* Visualization
* Similarity search
* Nearest-neighbour preprocessing
* Bioinformatics
* AI heuristic search

---
  