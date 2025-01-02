#include <iostream>
#include <vector>

void func(std::vector<int> values, int value) {
    values.push_back(value);
    for (auto x : values) {
        std::cout << x << "\n";
    }
    values = {1, 2, 3};
}

int main(int argc, char *argv[]) {
    std::vector<int> v = {10, 20};
    func(v, 30);
    std::cout << "------\n";
    for (auto x : v) {
        std::cout << x << "\n";
    }
    return 0;
}
