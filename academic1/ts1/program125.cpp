/*
   exercise: 125
   page: 260
   description: copy file
   command: echo file1.txt file3.txt | ./program125
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    std::string file1, file2;
    std::cin >> file1 >> file2;

    std::fstream f1(file1, std::ios::in);
    std::fstream f2(file2, std::ios::out);
    char ch;
    while(f1 >> std::resetiosflags(std::ios::skipws) >> ch) f2 << ch;
    f1.close();
    f2.close();

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

