/*
   exercise: 043
   page: 178
   description: conjectura lui goldbach
   command: echo 122 | ./program043
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n;
    std::cin >> n;
    if (n % 2 != 0) {
        std::cout << "[ RESULT ] " << n << " is not even\n";
    } else {
        for (int i = 2; i <= n / 2; i++) {
            bool is_prime = true;
            for (int j = 2; j < i; j++) {
                if (i % j == 0) is_prime = false;
            }
            if (is_prime) {
                bool diff_is_prime = true;
                for (int k = 2; k < n - i; k++) {
                    if ((n - i) % k == 0) diff_is_prime = false;
                }
                if (diff_is_prime) {
                    std::cout << "[ RESULT ] " << i << ", " << n - i << "\n";
                }
            }
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

