#include <iostream>

int main(int argc, char *argv[]) {
    char a[] = {-65, 16, 14, 5, 3, 3, 1, 14, 1, 0};
    for (int i = 0; i < 10; i++) std::cout << (char)(100 + a[i]);
    std::cout << "\n";
    return 0;
}
