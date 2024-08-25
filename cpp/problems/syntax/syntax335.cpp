#include <iostream>

int main(int argc, char *argv[]) {
    auto plus = [value=1](int x) { return x + value; };

    assert(plus(42) == 43);
    std::cout << plus(42) << "\n";
    return 0;
}
