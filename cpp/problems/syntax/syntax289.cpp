#include <iostream>

int main(int argc, char *argv[]) {
    int a = 0, b = 1, c;

    for (int i = 0; i < 46; i++) {
        std::cout << b << " " << a << " " << ((float) b) / ((float) a) << "\n";
        c = b;
        b += a;
        a = c;
    }

    return 0;
}
