/*
   exercise: 131
   page: 262
   description: replace first 4 chars in a file with "tata"
   command: ./program131
*/

#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>
#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    std::fstream f("file7.txt", std::ios::in | std::ios::out);
    char cuvant[10];
    f >> cuvant;
    std::cout << cuvant << std::endl;
    f.seekp(0, std::ios::beg);
    std::strcpy(cuvant, "tata");
    f << cuvant;
    f.close();

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

