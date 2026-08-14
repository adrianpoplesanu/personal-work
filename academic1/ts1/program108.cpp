/*
   exercise: 108
   description: multiply natural numbers stored in fixed arrays of 50 digits
   command: echo 128 999 | ./program108
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

const int SIZE = 50;

void storeNumber(long long number, int digits[]) {
    for (int i = 0; i < SIZE; i++) {
        digits[i] = 0;
    }

    for (int i = SIZE - 1; i >= 0 && number > 0; i--) {
        digits[i] = number % 10;
        number /= 10;
    }
}

void multiply(const int a[], const int b[], int product[]) {
    for (int i = 0; i < SIZE; i++) {
        product[i] = 0;
    }

    // The units digits are at index 49, so i + j - 49 is the result index.
    for (int i = SIZE - 1; i >= 0; i--) {
        for (int j = SIZE - 1; j >= 0; j--) {
            int resultIndex = i + j - (SIZE - 1);
            if (resultIndex >= 0) {
                product[resultIndex] += a[i] * b[j];
            }
        }
    }

    for (int i = SIZE - 1; i > 0; i--) {
        product[i - 1] += product[i] / 10;
        product[i] %= 10;
    }
}

void displayArray(const int digits[]) {
    for (int i = 0; i < SIZE; i++) {
        std::cout << digits[i];
    }
    std::cout << '\n';
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    long long firstNumber, secondNumber;
    int a[SIZE], b[SIZE], product[SIZE];

    std::cin >> firstNumber >> secondNumber;
    storeNumber(firstNumber, a);
    storeNumber(secondNumber, b);
    multiply(a, b, product);

    std::cout << "First number:\n";
    displayArray(a);
    std::cout << "Second number:\n";
    displayArray(b);
    std::cout << "Product:\n";
    displayArray(product);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
