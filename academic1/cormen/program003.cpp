/*
   exercise: 003
   page: 22
   description: linear search
   command: echo 9 3 8 2 7 1 6 -9 4 5 10 | ./program003
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

int linear_search(int a[], int n, int v) {
    int i;
    for(i = 0; i < n; i++) {
        if(a[i] == v) {
            return i;
        }
    }
    return -1;
}

void read_array(int a[], int &n) {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n, i, v;
    read_array(a, n);
    std::cin >> v;

    int result = linear_search(a, n, v);
    std::cout << "[ RESULT ] " << result << "\n";

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

