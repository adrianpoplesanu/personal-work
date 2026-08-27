/*
   exercise: 130
   page: 262
   description: write to a file only if it does not exist
   command: echo file6.txt ala bala portocala | ./program130
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
    std::fstream g(file, std::ios::out);
    char ch;
    if (f) {
        std::cout << "File already exists!" << std::endl;
    } else {
        while(std::cin >> std::resetiosflags(std::ios::skipws) >> ch) g << ch;
    }
    f.close();
    g.close();

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

