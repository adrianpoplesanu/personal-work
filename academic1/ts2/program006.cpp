/*
   exercise: 006
   page: 14
   description: masive si pointeri de masive
   command: ./program006
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    float g[7][8][3], (*a)[8][3], (*b)[3], *c;

    g[2][3][1] = 15;
    a = g;
    std::cout << a[2][3][1] << "\n";

    b = g[2];
    std::cout << b[3][1] << "\n";

    c = g[2][3];
    std::cout << c[1] << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

