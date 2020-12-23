// ts2 p34 e1
#include <iostream>
using namespace std;

void vector (int x[10]) {
    for (int i = 0; i < 10; i++) x[i] = i;
}

int main(int argc, char *argv[]) {
    int a[10];
    vector(a);
    for (int i = 0; i < 10; i++) cout << a[i] << " ";
    cout << '\n';
    return 0;
}
