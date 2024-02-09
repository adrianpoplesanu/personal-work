#include <iostream>

const int BASE = 10000;
const int SIZE = 10000;

void init(int a[SIZE]) {
    for (int i = 0; i < SIZE; i++) a[i] = 0;
}

void copy(int a[SIZE], int b[SIZE]) {
    for (int i = 0; i < SIZE; i++) b[i] = a[i];
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

void print(int a[SIZE]) {
    int found = false;
    for (int i = 9999; i >= 0; i--) {
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

int main(int argc, char *argv[]) {
    int a[SIZE], b[SIZE], c[SIZE];
    init(a);
    init(b);
    init(c);

    b[0] = 1;

    int i = 0;
    while (i < 100000) {
        sum(a, b, c);
        copy(b, a);
        copy(c, b);
        i++;
    }

    print(a);
    std::cout << "\n";

    return 0;
}
