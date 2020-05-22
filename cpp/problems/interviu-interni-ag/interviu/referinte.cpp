#include <iostream>
using namespace std;

void set(int a) {
    a = 7;
}

int main(int argc, char *argv[]) {
    int a = 5;
    set(a);
    cout << a << endl;
    return 0;
}
