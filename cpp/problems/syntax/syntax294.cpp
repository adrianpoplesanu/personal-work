#include <iostream>

const int BASE = 10000;

void init(int a[10000]) {
    for (int i = 0; i < 10000; i++) {
        a[i] = 0;
    }
}

void sum(int a[10000], int b[10000], int c[10000]) {
    int remainder = 0;
    for (int i = 0; i < 10000; i++) {
        c[i] = a[i] + b[i] + remainder;
        remainder = 0;
        while (c[i] >= BASE) {
            c[i] -= BASE;
            remainder++;
        }
    }
}

void print_digit(int val, bool first) {
    if (first) {
        std::cout << val;
    } else {
        if (val < 10) {
            std::cout << "000" << val;
        } else if (val < 100) {
            std::cout << "00" << val;
        } else if (val < 1000) {
            std::cout << "0" << val;
        }  else {
            std::cout << val;
        }
    }
}

void print(int a[10000]) {
    bool found = false;
    for (int i = 9999; i >= 0; i--) {
        if (!found) {
            if (a[i] != 0) {
                print_digit(a[i], true);
                found = true;
            } else if (i == 0) {
                std::cout << 0;
            }
        } else {
            print_digit(a[i], false);
        }
    }
}

void copy(int a[10000], int b[10000]) {
    for (int i = 0; i < 10000; i++) a[i] = b[i];
}

int main(int argc, char *argv[]) {
    int a[10000], b[10000], c[10000];

    init(a);
    init(b);
    b[0] = 1;
    init(c);

    int i = 0;
    while (i < 100000) {
        sum(a, b, c);
        copy(a, b);
        copy(b, c);
        i++;
    }

    print(a);
    std::cout << "\n";

    return 0;
}
