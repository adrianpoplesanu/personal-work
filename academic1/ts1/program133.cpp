/*
   exercise: 133
   page: 263
   description: print all the characters from a file that are in a given range positions
   command: echo 1 10./program133
*/

#include <iostream>
#include <fstream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    std::fstream f("file8.txt", std::ios::in);
    int i, j;
    std::cin >> i >> j;
    char ch;

    f.seekp(i, std::ios::beg);
    while(f.tellp() < j) {
        //f >> ch;
        f.get(ch);
        if(f.eof()) break;
        std::cout << ch;
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

