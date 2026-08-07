/*
   exercise: 020
   page: 126
   description: randomize array in place
   command: echo 9 1 2 3 4 5 6 7 8 9 | ./program020
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void read_array(int a[50], int &n) {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
}

void print_array(int a[50], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

void randomize_in_place(int a[50], int n) {
    for (int i = 0; i < n; i++) {
        int pos = i + (rand() % (n - i));
        int tmp = a[i];
        a[i] = a[pos];
        a[pos] = tmp;
    }
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    //... start code here

    int a[50], n;
    read_array(a, n);

    srand(time(nullptr));
    randomize_in_place(a, n);

    print_array(a, n);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

