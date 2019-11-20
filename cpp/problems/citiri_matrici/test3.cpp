#include <iostream>
using namespace std;

void test(int *a) {
    a = new int[5];
    cout << a << endl;
    a[0] = 23;
    a[1] = 34;
    a[2] = 45;
    a[3] = 56;
    a[4] = 67;
    cout << a[0] << a[1] << a[2] << a[3] << a[4] << endl;
}

int main(int argc, char *argv[]) {
    int *a;
    cout << a << endl;
    test(a);
    cout << a << endl;
    return 0;
}
