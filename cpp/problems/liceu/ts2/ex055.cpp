// ts2 p32 e1
#include <iostream>
using namespace std;

void test(int n) {
    n += 1;
    cout << n << '\n';
}

int main(int argc, char *argv[]) {
    int n = 1;
    test (n);
    cout << n << '\n';
    return 0;
}
