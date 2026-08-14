/*
   exercise: 105
   description: store a natural number in an array and multiply it by one digit
   command: echo 5 128 7 | ./program105
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void storeNumberInArray(int number, int a[], int size) {
    for (int i = 0; i < size; i++) {
        a[i] = 0;
    }

    for (int i = size - 1; i >= 0 && number > 0; i--) {
        a[i] = number % 10;
        number /= 10;
    }
}

void multiplyByDigit(const int a[], int size, int multiplier,
                     int result[], int& resultSize) {
    int carry = 0;

    for (int i = size - 1; i >= 0; i--) {
        int product = a[i] * multiplier + carry;
        result[i + 1] = product % 10;
        carry = product / 10;
    }

    result[0] = carry;
    resultSize = size + 1;
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

    const int MAX_SIZE = 50;
    int a[MAX_SIZE], result[MAX_SIZE + 1];
    int size, number, multiplier, resultSize;

    std::cin >> size >> number >> multiplier;
    storeNumberInArray(number, a, size);
    multiplyByDigit(a, size, multiplier, result, resultSize);

    std::cout << "Number in array: ";
    displayArray(a, size);
    std::cout << "Product in array: ";
    displayArray(result, resultSize);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
