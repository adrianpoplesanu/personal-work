#include <iostream>
using namespace std;

void change_values(int *&a) {
    for (int i = 0; i < 10; i++) a[i] = 7;
}

int main(int argc, char *argv[]) {
    int *a;
    a = new int[10];
    change_values(a);
    for (int i = 0; i < 10; i++) cout << a[i];
    cout << endl;
    return 0;
}
