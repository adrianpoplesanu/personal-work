#include <iostream>

void test(int a[3]) {
    int *b;
    b = a;
    b[0] = 7;
}

int main(int argc, char *argv[]) {
    int a[3] = { 1, 2, 3};
    test(a);
    for (int i = 0; i < 3; i++) {
        std::cout << a[i] << "\n";
    }
    return 0;
}
