/*
   exercise: 048
   page: 180
   description: suma tuturor numerelor cu cifre impare de maxim 5 cifre
   command: ./program048
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int sum = 0;
    for(int i = 1; i <= 99999; i += 2) {
        int current = i;
        bool is_eligible = true;
        while(current) {
            if (((current % 10) % 2) == 0) is_eligible = false;
            current /= 10;
        }
        if (is_eligible) {
            current = i;
            while(current) {
                sum += current % 10;
                current /= 10;
            }
        }
    }
    std::cout << "[ RESULT ] " << sum << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

