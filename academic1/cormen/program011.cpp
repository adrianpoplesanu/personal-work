/*
   exercise: 000
   page: 00
   description: testing template
   command: echo 9 3 8 2 7 1 6 9 4 5 | ./program011
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void bubble_sort(int a[], int n) {
    int i, sorted, tmp;
    sorted = 0;
    while(!sorted) {
        sorted = 1;
        for (i = 0; i < n - 1; i++) {
            if (a[i] > a[i + 1]) {
                sorted = 0;
                tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
            }
        }
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
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);
    bubble_sort(a, n);
    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

