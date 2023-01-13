#include <iostream>

void change_value(int &a) {
    a = 7;
}

void change_value2(int a) {
    a = 9;
}

int main(int argc, char *argv[]) {

    int a = 5;
    std::cout << a << "\n";
    change_value(a);
    std::cout << a << "\n";
    change_value2(a);
    std::cout << a << "\n";

    return 0;
}
