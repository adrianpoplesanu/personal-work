#include <iostream>
using namespace std;

int test(int &a) {
    a++;
    return a;
}

int main(int argc, char *argv[]) {
    int a = 5;
    cout << a << endl;
    cout << test(a) << endl;
    cout << a << endl;
    return 0;
}
