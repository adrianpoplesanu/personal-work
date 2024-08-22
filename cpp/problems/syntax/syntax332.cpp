#include <iostream>

class Plus {
    int value;
public:
    Plus(int v) { value = v; }

    int operator() (int x) const {
        return x + value;
    }
};

int main(int argc, char *argv[]) {
    Plus plus(1);
    auto a = plus(42);

    std::cout << a << "\n";
    return 0;
}
