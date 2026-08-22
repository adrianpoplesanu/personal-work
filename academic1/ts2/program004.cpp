/*
   exercise: 004
   page: 10
   description: bit mask for printing octets
   command: echo 123 | ./program020
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a=257, i, j, mask;
    char *adr_byte = (char *) &a;
    for (i = 0; i < sizeof(a); i++) {
        mask = 128;
        for (j = 0; j < 8; j++) {
            if (*adr_byte & mask) {
                std::cout << 1;
            } else {
                std::cout << 0;
            }
            mask >>= 1;
        }
        adr_byte++;
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

