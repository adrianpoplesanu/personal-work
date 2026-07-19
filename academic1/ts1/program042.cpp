/*
   exercise: 042
   page: 178
   description: n pairs of consecutive primes
   command: echo 5 | ./program042
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    std::cin >> n;
    int old1 = 2;
    int old2 = 3;
    int current = 3;

    while(n) {
        bool found = false;
        while(!found) {
            current++;
            bool is_prime = true;
            for (int i = 2; i < current; i++) {
                if (current % i == 0) is_prime = false;
            }
            if (is_prime) {
                found = 1;
                old1 = old2;
                old2 = current;
            }
        }
        if (old1 + 2 == old2) {
            std::cout << "[ RESULT ] (" << old1 << ", " << old2 << ")\n";
            n--;
        }
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

