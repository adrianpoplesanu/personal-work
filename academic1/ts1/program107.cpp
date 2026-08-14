/*
   exercise: 107
   description: multiply two natural numbers represented as digit arrays
   command: echo 5 128 4 999 | ./program107
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

const int MAX_SIZE = 50;

void storeNumberInArray(int number, int a[], int size) {
    for (int i = 0; i < size; i++) {
        a[i] = 0;
    }

    for (int i = size - 1; i >= 0 && number > 0; i--) {
        a[i] = number % 10;
        number /= 10;
    }
}

void multiplyDigitArrays(const int a[], int n, const int b[], int m,
                         int product[], int& productSize) {
    int temporary[2 * MAX_SIZE] = {0};

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            temporary[i + j + 1] += a[i] * b[j];
        }
    }

    for (int i = n + m - 1; i > 0; i--) {
        temporary[i - 1] += temporary[i] / 10;
        temporary[i] %= 10;
    }

    int firstDigit = 0;
    while (firstDigit < n + m - 1 && temporary[firstDigit] == 0) {
        firstDigit++;
    }

    productSize = n + m - firstDigit;
    for (int i = 0; i < productSize; i++) {
        product[i] = temporary[firstDigit + i];
    }
}

void displayArray(const int a[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[MAX_SIZE], b[MAX_SIZE], product[2 * MAX_SIZE];
    int n, m, firstNumber, secondNumber, productSize;

    std::cin >> n >> firstNumber >> m >> secondNumber;
    storeNumberInArray(firstNumber, a, n);
    storeNumberInArray(secondNumber, b, m);
    multiplyDigitArrays(a, n, b, m, product, productSize);

    std::cout << "First number: ";
    displayArray(a, n);
    std::cout << "Second number: ";
    displayArray(b, m);
    std::cout << "Product: ";
    displayArray(product, productSize);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
