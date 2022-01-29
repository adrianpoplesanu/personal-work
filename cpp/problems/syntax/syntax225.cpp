#include <iostream>

void test(int a[100]) {
    for (int i = 0; i < 100; i++) a[i] = i;
}

void print(int a[100]) {
    for (int i = 0; i < 100; i++) std::cout << a[i] << " ";
    std::cout << "\n";
}

void print2(int a[], int n) {
    for (int i = 0; i < n; i++) std::cout << a[i] << " ";
    std::cout << "\n";
}

void print3(int *a, int n) {
    for (int i = 0; i < n; i++) std::cout << a[i] << " ";
    std::cout << "\n";
}

int main(int argc, char *argv[]) {
    int a[100];
    test(a);
    print(a);
    print2(a, 100);
    print3(a, 100);
    return 0;
}
