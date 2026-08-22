/*
   exercise: 003
   page: 09
   description: bit mask
   command: ./program003
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a = 5, j;
    int mask = 128;
    char *adr_byte = (char*) &a;
    for (j = 0; j < 8; j++) {
        if (*adr_byte & mask) {
            std::cout << 1;
        } else {
            std::cout << 0;
        }
        *adr_byte = *adr_byte << 1;
    }
    std::cout << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

