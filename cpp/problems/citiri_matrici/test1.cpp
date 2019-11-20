#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int *a;
    a = new int[5];
    a[0] = 1;
    cout << a[0] << endl;
    return 0;
}
