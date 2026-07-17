/*
   exercise: 035
   page: 00
   description: testing template
   command: echo 12 56 34 19 | ./program035
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int num, min, max, mij1, mij2;
    std::cin >> num;
    min = num;
    max = num;
    std::cin >> num;
    if (num < min) {
        min = num;
    } else {
        max = num;
    }
    std::cin >> num;
    if (num < min) {
        mij1 = min;
        min = num;
    } else if (num > max) {
        mij1 = max;
        max = num;
    } else {
        mij1 = num;
    }
    std::cin >> num;
    if (num < min) {
        mij2 = min;
        min = num;
    } else if (num > max) {
        mij2 = max;
        max = num;
    } else {
        mij2 = num;
    }
    if (mij1 < mij2) {
        std::cout << "[ RESULT ] " << min << " " << mij1 << " " << mij2 << " " << max << " \n";
    } else {
        std::cout << "[ RESULT ] " << min << " " << mij2 << " " << mij1 << " " << max << " \n";
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

