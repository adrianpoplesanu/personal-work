/*
   exercise: 126
   page: 261
   description: formated file conainting first n numbers in hex format
   command: echo 100 | ./program126
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    std::cin >> n;
    std::fstream f("file5.txt", std::ios::out);
    for(int i = 0; i < n; i++) {
        f << std::setw(5)<< std::hex << i << std::endl;
    }
    f.close();

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

