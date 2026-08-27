/*
   exercise: 127
   page: 261
   description: print file content from hex to decimal
   command: echo file5.txt | ./program127
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    std::string file;
    std::cin >> file;

    std::fstream f(file, std::ios::in);
    int n;
    while(f >> std::hex >> n) std::cout << std::dec << n << std::endl;
    f.close();

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

