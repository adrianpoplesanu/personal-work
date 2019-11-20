#include <iostream>
using namespace std;

void test() {
    int *a;
    a = new int[5];
    a[0] = 23;
    cout << a[0] << endl;
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}
