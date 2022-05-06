#include <iostream>

int main(int argc, char* argv[]) {
    int a[] = {1, 2, 3, 4};
    std::cout << a[1] << "\n";
    std::cout << *(a + 1) << "\n";
    std::cout << *(1 + a) << "\n";
    std::cout << 1[a] << "\n";
    return 0;
}
