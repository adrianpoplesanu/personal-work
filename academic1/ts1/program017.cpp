/*
   exercise: 017
   page: 131
   description: numere care sunt sume de cuburi
   command: ./program017
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int i1, j1, i2, j2;
    for (int n = 1; n < 10000; n++) {
        int nr = 0;
        for (int i = 1; i < 22; i++) {
            for(int j = i; j < 22; j++) {
                if (n == i * i * i + j * j * j) {
                    if (nr == 0) {
                        i1 = i;
                        j1 = j;
                    } else {
                        i2 = i;
                        j2 =j;
                    }
                    nr++;
                }
            }
        }
        if (nr == 2) {
            std::cout << "[ RESULT ] " << n << " (" << i1 << ", " << j1 <<") (" << i2 << ", " << j2 <<") \n";
        }
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "[ log ] Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

