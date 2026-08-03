/*
   exercise: 082
   page: 231
   description: itoa
   command: ./program082
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int i = 123;
    char buffer [sizeof(int)*8+1];

    snprintf(buffer, sizeof(buffer), "%d", i);

    std::cout << "[ RESULT ] " << buffer << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

