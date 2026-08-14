/*
   exercise: 101
   description: decompose the digits of a number into an array
   command: echo 3124 | ./program101
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int n, a[50], reverseDigits[50], count = 0;
    std::cin >> n;

    if (n == 0) {
        a[count++] = 0;
    } else {
        if (n < 0) n = -n;

        while (n > 0) {
            reverseDigits[count++] = n % 10;
            n /= 10;
        }

        for (int i = 0; i < count; i++) {
            a[i] = reverseDigits[count - 1 - i];
        }
    }

    for (int i = 0; i < count; i++) {
        std::cout << "a[" << i << "] = " << a[i] << '\n';
    }

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
