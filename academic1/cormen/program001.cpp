/*
   exercise: 001
   page: 18
   description: insertion sort
   command: echo 9 3 8 2 7 1 6 -9 4 5 | ./program001
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void insertion_sort(int a[], int n) {
    int i, j, key;
    for (j = 1; j < n; j++) {
        key = a[j];
        i = j - 1;
        while(i >= 0 && a[i] > key) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
    }
}

void read_array(int a[], int &n) {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
}

void print_array(int a[], int n) {
    for(int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);

    insertion_sort(a, n);

    std::cout << "[ RESULT ] ";
    print_array(a, n);
    std::cout << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

