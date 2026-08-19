/*
   exercise: 119
   page: 246
   description: sa elements in matrix
   command: echo 4 4 5 1 2 3 7 5 2 3 8 5 6 8 9 10 11 12 | ./program119
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_matrix(int a[50][50], int &n, int &m) {
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
}

void print_matrix(int a[50][50], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool is_sa(int a[50][50], int n, int m, int i, int j) {
    bool good = true;
    for (int z = 0; z < m; z++) {
        if (a[i][j] < a[i][z]) good = false;
    }
    for (int z = 0; z < n; z++) {
        if (a[i][j] > a[z][i]) good = false;
    }
    if (good) return true;
    good = true;
    for (int z = 0; z < m; z++) {
        if (a[i][j] > a[i][z]) good = false;
    }
    for (int z = 0; z < n; z++) {
        if (a[i][j] < a[z][j]) good = false;
    }
    if (good) return true;
    return false;
}

void resolve(int a[50][50], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (is_sa(a, n, m, i, j)) {
                std::cout << a[i][j] << " ";
            }
        }
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50][50], n, m;
    read_matrix(a, n, m);
    print_matrix(a, n, m);

    resolve(a, n, m);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

