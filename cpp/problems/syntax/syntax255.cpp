#include <iostream>

void change_value(int *a) {
    *a = 7;
}

int main(int argc, char *argv[]) {
    int *a = new int();
    *a = 5;

    std::cout << *a << "\n";
    change_value(a);
    std::cout << *a << "\n";

    delete a;

    return 0;
}
