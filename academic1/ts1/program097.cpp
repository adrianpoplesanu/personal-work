/*
   exercise: 097
   description: sort pairs of numbers by their ratios
   command: echo 4 3 1 2 1 4 2 3 4 | ./program097
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void insertionSort(int a[], int b[], int n) {
    for (int i = 1; i < n; i++) {
        int currentA = a[i];
        int currentB = b[i];
        int j = i - 1;

        while (j >= 0 && static_cast<double>(a[j]) / b[j] >
                            static_cast<double>(currentA) / currentB) {
            a[j + 1] = a[j];
            b[j + 1] = b[j];
            j--;
        }
        a[j + 1] = currentA;
        b[j + 1] = currentB;
    }
}

void bubbleSort(int a[], int b[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (static_cast<double>(a[j]) / b[j] >
                static_cast<double>(a[j + 1]) / b[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }
}

void displayRatios(const int a[], const int b[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << '/' << b[i] << ' ';
    }
    std::cout << '\n';
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], b[50], insertionA[50], insertionB[50];
    int bubbleA[50], bubbleB[50], n;

    std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> a[i];
    for (int i = 0; i < n; i++) std::cin >> b[i];

    for (int i = 0; i < n; i++) {
        insertionA[i] = bubbleA[i] = a[i];
        insertionB[i] = bubbleB[i] = b[i];
    }

    insertionSort(insertionA, insertionB, n);
    bubbleSort(bubbleA, bubbleB, n);

    std::cout << "Insertion sort: ";
    displayRatios(insertionA, insertionB, n);
    std::cout << "Bubble sort: ";
    displayRatios(bubbleA, bubbleB, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}
