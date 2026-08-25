/*
   exercise: 120
   page: 259
   description: write to a text file
   command: echo -e "buna dimineata\nbebe dex" | ./program120
   atentia: scrii la tastatura si apesi Ctrl-D
*/

#include <iostream>
#include <fstream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    std::fstream f("file1.txt", std::ios::out);
    char ch;
    while(std::cin >> ch) f << ch;
    f.close();

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

