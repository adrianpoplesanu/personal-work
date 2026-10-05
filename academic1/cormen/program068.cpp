/*
   exercise: 068
   page: 402
   description: optimal binary search tree
   command: echo 5 0.15 0.10 0.05 0.10 0.20 0.05 0.10 0.05 0.05 0.05 0.10 | ./program068
   command: echo 7 0.04 0.06 0.08 0.02 0.10 0.12 0.14 0.06 0.06 0.06 0.06 0.05 0.05 0.05 0.05 | ./program068
*/

#include <iostream>
#include <limits>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_probabilities(double p[50], double q[50], int &n) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> p[i];
    }
    for (int i = 0; i <= n; i++) {
        std::cin >> q[i];
    }
}

// algorithm 15.5 clrs
void optimal_bst(double p[50], double q[50], int n, double e[50][50], int root[50][50]) {
    double w[50][50];

    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = std::numeric_limits<double>::infinity();
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
}

void construct_optimal_bst(int root[50][50], int i, int j, int parent, const char *side) {
    if (i <= j) {
        int r = root[i][j];
        if (parent == 0) {
            std::cout << "k" << r << " is the root\n";
        } else {
            std::cout << "k" << r << " is the " << side << " child of k" << parent << "\n";
        }
        construct_optimal_bst(root, i, r - 1, r, "left");
        construct_optimal_bst(root, r + 1, j, r, "right");
    } else {
        std::cout << "d" << j << " is the " << side << " child of k" << parent << "\n";
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    double p[50], q[50];
    int n;
    read_probabilities(p, q, n);

    double e[50][50];
    int root[50][50];
    optimal_bst(p, q, n, e, root);

    std::cout << e[1][n] << "\n";
    construct_optimal_bst(root, 1, n, 0, "");

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

