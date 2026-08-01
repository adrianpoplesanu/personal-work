/*
   exercise: 005
   page: 29
   description: selection sort
   command: echo 9 3 8 2 7 1 6 -9 4 5 | ./program005
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void selection_sort(int a[], int n) {
    int i, j, min, tmp;
    for (i = 0; i < n; i++) {
        min = i;
        for(j = i + 1; j < n; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        tmp = a[i];
        a[i] = a[min];
        a[min] = tmp;
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
    selection_sort(a, n);
    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

