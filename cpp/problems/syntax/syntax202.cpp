#include <iostream>

int main(int argc, char *argv[]) {
    int **data;
    data = new int*[3];
    int a = 1, b = 2, c = 3;
    data[0] = &a;
    data[1] = &b;
    data[2] = &c;

    for (int i = 0; i < 3; i++) {
        std::cout << *data[i] << " ";
    }
    std::cout << "\n";

    // this works which is cool
    // once this method is done and the stack is freed data[i] will point to freed memory space
    return 0;
}
