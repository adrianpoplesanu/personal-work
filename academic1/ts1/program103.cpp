/*
   exercise: 103
   description: count the trailing zeroes in the product of array elements
   command: echo 4 10 25 12 4 | ./program103
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int countFactor(int number, int factor) {
    int count = 0;
    while (number % factor == 0) {
        count++;
        number /= factor;
    }
    return count;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    int factorsOf2 = 0, factorsOf5 = 0;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];

        int number = a[i];
        if (number < 0) number = -number;

        if (number == 0) {
            std::cout << "The product is 0.\n";
            return 0;
        }

        factorsOf2 += countFactor(number, 2);
        factorsOf5 += countFactor(number, 5);
    }

    int trailingZeroes = (factorsOf2 < factorsOf5) ? factorsOf2 : factorsOf5;
    std::cout << "Trailing zeroes: " << trailingZeroes << '\n';

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
