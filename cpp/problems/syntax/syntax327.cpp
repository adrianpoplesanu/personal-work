#include <iostream>

// cppcon lambdas series
// https://www.youtube.com/watch?v=3jCOwajNch0&list=RDQM0eYw2efAwBQ&start_radio=1&ab_channel=CppCon

int plus1(int x) {
    return x + 1;
}

int main(int argc, char *argv[]) {
    int a = 5;
    std::cout << plus1(a) << "\n";
    return 0;
}
