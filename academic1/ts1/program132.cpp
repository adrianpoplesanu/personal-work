/*
   exercise: 132
   page: 262
   description: read a text file containing multiple lines, some empty and print the file content to the console
   command: ./program132
*/

#include <iostream>
#include <fstream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    std::fstream f("file8.txt", std::ios::in);
    char line[100];
    // asta nu merge, ts n-a avut dreptate
    /*while(f.get(line, 100)) {
        std::cout << line << std::endl;
        f.get();
    }*/
    while(f.getline(line, 100)) {
        std::cout << line << std::endl;
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

