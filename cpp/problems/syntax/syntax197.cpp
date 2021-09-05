#include <iostream>

int main(int argc, char *argv[]) {
    int a[2][3] = {
        { 1, 2, 3 },
        { 4, 5, 6 }
    };
    int *p;
    p = a[0];
    int (*b)[3];
    b = a;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) std::cout << b[i][j] << " ";
        std::cout << "\n";
    }
    return 0;
}
