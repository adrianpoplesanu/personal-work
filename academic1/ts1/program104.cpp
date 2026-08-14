/*
   exercise: 104
   description: calculate 2^100 using an array of decimal digits
   command: ./program104
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

const int MAX_DIGITS = 100;

void handleCarry(int digits[], int& digitCount) {
    for (int i = 0; i < digitCount; i++) {
        if (digits[i] >= 10) {
            if (i + 1 == digitCount) {
                digits[digitCount++] = 0;
            }
            digits[i + 1] += digits[i] / 10;
            digits[i] %= 10;
        }
    }
}

void multiplyByDigit(int digits[], int& digitCount, int multiplier) {
    for (int i = 0; i < digitCount; i++) {
        digits[i] *= multiplier;
    }
    handleCarry(digits, digitCount);
}

void displayNumber(const int digits[], int digitCount) {
    for (int i = digitCount - 1; i >= 0; i--) {
        std::cout << digits[i];
    }
    std::cout << '\n';
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int digits[MAX_DIGITS] = {1};
    int digitCount = 1;

    for (int power = 0; power < 100; power++) {
        multiplyByDigit(digits, digitCount, 2);
    }

    std::cout << "2^100 = ";
    displayNumber(digits, digitCount);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
