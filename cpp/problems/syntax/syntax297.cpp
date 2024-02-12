#include <iostream>

const int BASE = 10000;
const int SIZE = 10000;

void init(int a[SIZE]) {
    for (int i = 0; i < SIZE; i++) a[i] = 0;
}

void copy(int a[SIZE], int b[SIZE]) {
    for (int i = 0; i < SIZE; i++) a[i] = b[i];
}

void print_digit(int val) {
    if (val < 10) {
        std::cout << "000" << val;
    } else if (val < 100) {
        std::cout << "00" << val;
    } else if (val < 1000) {
        std::cout << "0" << val;
    } else {
        std::cout << val;
    }
}

void sum(int a[SIZE], int b[SIZE], int c[SIZE]) {
    int remainder = 0;
    for (int i = 0; i < SIZE; i++) {
        c[i] = a[i] + b[i] + remainder;
        remainder = 0;
        while (c[i] >= BASE) {
            c[i] -= BASE;
            remainder++;
        }
    }
}

void print(int a[SIZE]) {
    bool found = false;
    for (int i = SIZE - 1; i >= 0; i--) {
        if (!found) {
            if (a[i] != 0) {
                found = true;
                std::cout << a[i];
            }
        } else {
            print_digit(a[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    int a[SIZE], b[SIZE], c[SIZE];

    init(a);
    init(b);
    init(c);

    b[0] = 1;

    int i = 0;
    while (i < 15000) {
        sum(a, b, c);
        copy(a, b);
        copy(b, c);
        i++;
    }

    print(a);
    std::cout << "\n";

    return 0;
}
