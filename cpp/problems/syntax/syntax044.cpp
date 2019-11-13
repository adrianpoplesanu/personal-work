#include <iostream>
using namespace std;

void increment(int *a) {
    (*a)++;
}

void increment2(int &b) {
    b++;
}

int main(int argc, char *argv[]) {
    int a = 4;
    increment(&a);
    cout << a << endl;

    int *b = &a;
    increment(b);
    cout << *b << endl;

    increment2(a);
    cout << a << endl;
    return 0;
}
