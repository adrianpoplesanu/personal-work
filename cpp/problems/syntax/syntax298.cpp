#include <iostream>

int main(int argc, char *argv[]) {
    int a[3];
    a[0] = 11;
    a[1] = 22;
    a[2] = 33;

    int i = 1;
    std::cout << a[i] << "\n";
    std::cout << *(a + i) << "\n";
    std::cout << *(i + a) << "\n";
    std::cout << i[a] << "\n";
    std::cout << 1[a] << "\n";

    return 0;
}
