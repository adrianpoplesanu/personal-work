/*
   exercise: 106
   description: add two natural numbers represented as digit arrays
   command: echo 5 128 4 999 | ./program106
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

void addDigitArrays(const int a[], int n, const int b[], int m,
                    int sum[], int& sumSize) {
    int i = n - 1;
    int j = m - 1;
    int k = MAX_SIZE + 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digitA = (i >= 0) ? a[i--] : 0;
        int digitB = (j >= 0) ? b[j--] : 0;
        int total = digitA + digitB + carry;

        sum[--k] = total % 10;
        carry = total / 10;
    }

    sumSize = MAX_SIZE + 1 - k;
    for (int index = 0; index < sumSize; index++) {
        sum[index] = sum[k + index];
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

    int a[MAX_SIZE], b[MAX_SIZE], sum[MAX_SIZE + 1];
    int n, m, firstNumber, secondNumber, sumSize;

    std::cin >> n >> firstNumber >> m >> secondNumber;
    storeNumberInArray(firstNumber, a, n);
    storeNumberInArray(secondNumber, b, m);
    addDigitArrays(a, n, b, m, sum, sumSize);

    std::cout << "First number: ";
    displayArray(a, n);
    std::cout << "Second number: ";
    displayArray(b, m);
    std::cout << "Sum: ";
    displayArray(sum, sumSize);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
