#include <iostream>

int main(int argc, char *argv[]) {
    int a[] = { 1, 2, 3 };
    int *p;
    p = a;
    for (int i = 0; i < 3; i++) std::cout << *(p + i) << " ";
    for (int i = 0; i < 3; i++) std::cout << p[i] << " ";
    std::cout << "\n";
    return 0;
}
