#include <iostream>
#include <vector>

int test(std::vector<int> args) {
    std::cout << "test()\n";
    for (std::vector<int>::iterator it = args.begin(); it != args.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << '\n';
    return 113;
}

int main(int argc, char *argv[]) {
    int (*func)(std::vector<int>);

    func = &test;
    std::vector<int> a;
    a.push_back(2);
    a.push_back(3);
    a.push_back(5);

    func(a);

    return 0;
}
