/*
   exercise: 010
   page: 24
   description: mat struct
   command: echo 4 4 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 0.10 0.11 0.12 0.13 0.14 0.15 0.16 | ./program010
*/

#include <iostream>
#include <iomanip>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

struct Mat {
    float matrice[10][10];
};

Mat read(int n, int m) {
    Mat a;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a.matrice[i][j];
        }
    }
    return a;
}

void print(Mat a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << std::setw(4) << a.matrice[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, m;
    std::cin >> n >> m;
    Mat a = read(n, m);
    print(a, n, m);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

