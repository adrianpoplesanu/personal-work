/*
   exercise: 001
   page: https://info.mcip.ro/?cap=Programare%20dinamica
   description: #822
   command: ./program001
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[10][10] = {{1, 2, 3}, {-1, 3, 4}, {2, -1, 1}};
    int n = 3, i, j;
    int x[10][10];
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) x[i][j] = 0;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == 0) {
                x[i][j] = 1;
            } else if (j == 0) {
                x[i][j] = 1;
            } else {
                x[i][j] = x[i - 1][j - 1] + x[i - 1][j] + x[i][j - 1];
            }
        }
    }

    for(i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            std::cout << x[i][j] << " ";
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

