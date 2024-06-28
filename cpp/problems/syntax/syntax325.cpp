#include <iostream>

int main(int argc, char *argv[]) {
    int *a = new int(3);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    for (int i = 0; i < 3; i++) {
        std::cout << a[i] << "\n";
    }
    return 0;
}
