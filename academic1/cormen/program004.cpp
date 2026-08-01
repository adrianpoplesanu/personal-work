/*
   exercise: 000
   page: 00
   description: testing template
   command: echo 4 1 0 1 1 4 0 0 0 1 | ./program004
*/

#include <iostream>
#include <chrono>

#define PRINT_EXECUTION_DURATION 0

void n_bit_sum(int a[], int b[], int c[], int n) {
    int i, carry = 0;
    for (i = n - 1; i >= 0; i--) {
        c[i + 1] = a[i] + b[i] + carry;
        if (c[i + 1] > 1) {
            c[i + 1] -= 2;
            carry = 1;
        } else {
            carry = 0;
        }
    }
    c[0] = carry;
}

void n_bit_sum_cormen(int a[], int b[], int c[], int n) {
    int i, carry = 0;
    for (i = n - 1; i >= 0; i--) {
        c[i + 1] = (a[i] + b[i] + carry) % 2;
        if (a[i] + b[i] + carry >= 2) {
            carry = 1;
        } else {
            carry = 0;
        }
    }
    c[0] = carry;
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

    int a[50], b[50], c[50], n;
    read_array(a, n);
    read_array(b, n);
    n_bit_sum(a, b, c, n);
    print_array(c, n + 1);

    n_bit_sum_cormen(a, b, c, n);
    print_array(c, n + 1);

    //... end code here

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (PRINT_EXECUTION_DURATION) {
        std::cout << "Execution time: " << duration.count() << " ms\n";
    }
    return 0;
}

