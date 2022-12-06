#include <iostream>

void init(int a[20000]) {
    for (int i = 0; i < 20000; i++) {
        a[i] = 0;
    }
}

void copy_over(int a[20000], int b[20000]) {
    for (int i = 0; i < 20000; i++) b[i] = a[i];
}

void suma(int a[20000], int b[20000], int c[20000]) {
    init(c);
    for (int i = 0; i < 20000; i++) {
        c[i] += a[i] + b[i];
        if ( c[i] >= 10000 ) { c[i] -= 10000; c[i + 1]++; }
    }
}

void format(int n) {
    if (n == 0) {
        std::cout << "0000";
    } else if (n < 10) {
        std::cout << "000" << n;
    } else if (n < 100) {
        std::cout << "00" << n;
    } else if (n < 1000) {
        std::cout << "0" << n;
    } else {
        std::cout << n;
    }
}

int main(int argc, char *argv[]) {

    int a[20000], b[20000], c[20000];

    // b: 10000
    init(a);
    init(b);
    init(c);

    a[0] = 0;
    b[0] = 1;

    int i = 0;
    while (i < 100000) {
        suma(a, b, c);
        copy_over(b, a);
        copy_over(c, b);
        i++;
    }

    bool first = false;
    for (int i = 19999; i >= 0; i--) {
        if (a[i] != 0 && !first) {
            first = true;
            std::cout << a[i];
            continue;
        }
        if (first) {
            format(a[i]);
        }
    }

    return 0;
}
