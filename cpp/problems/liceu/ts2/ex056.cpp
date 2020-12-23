// ts2 p33 e1
#include <iostream>
using namespace std;

void test (int n) {
    cout << n << '\n';
}

int main(int argc, char *argv[]) {
    test (3);
    test(3 + 4 * 5);
    return 0;
}
