/*
   exercise: 065
   page: 211
   description: exchange two lines in a matrix
   command: echo 3 4 1 2 3 4 5 6 7 8 9 1 2 3 0 1 | ./program065
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50][50], n, m, i, j, l1, l2, tmp;
    std::cin >> n >> m;
    for(i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    std::cin >> l1 >> l2;
    for (i = 0; i < m; i++) {
        tmp = a[l1][i];
        a[l1][i] = a[l2][i];
        a[l2][i] = tmp;
    }

    std::cout << "[ RESULT ]\n";
    for(i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << "\n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

