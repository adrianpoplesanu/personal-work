/*
   exercise: 079
   page: 464
   description: table expansion
   command: ./program079
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void table_insert(int *&t, int &n, int &size, int value) {
    if (size == 0) {
        t = new int[1];
        size = 1;
    }
    if (n == size) {
        int *new_t = new int[2 * size];
        for (int i = 0; i < n; i++) {
            new_t[i] = t[i];
        }
        delete[] t;
        t = new_t;
        size = 2 * size;
    }
    t[n] = value;
    n++;
}

void printTable(int t[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << t[i] << " ";
    }
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int *t = nullptr, n = 0, size = 0;
    table_insert(t, n, size, 1);
    table_insert(t, n, size, 2);
    table_insert(t, n, size, 3);
    table_insert(t, n, size, 4);
    table_insert(t, n, size, 5);
    table_insert(t, n, size, 6);
    table_insert(t, n, size, 7);
    table_insert(t, n, size, 8);

    printTable(t, n);
    delete[] t;

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

