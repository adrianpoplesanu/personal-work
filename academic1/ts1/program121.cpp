/*
   exercise: 121
   page: 260
   description: reading from keyboard and saving to file with whitespaces
   command: echo -e "buna dimineata\nbebe dex" | ./program121
   atentie: cand rulezi trebuie sa apesi Ctrl-D pentru a termina inputul
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    std::fstream f("file2.txt", std::ios::out);
    char ch;
    while(std::cin >> std::resetiosflags(std::ios::skipws) >> ch) f << ch;
    f.close();

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

