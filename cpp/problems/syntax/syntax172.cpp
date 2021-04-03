// some array/matrix fun
#include <iostream>
using namespace std;

void func(int a[]) { // this does work
    //...
}

void func(int a[], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
}

void func2(int *a) {
    int i = 0;
    while(i < 5) {
        cout << *(a + i) << " ";
        i++;
    }
    cout << "\n";
}

void func3(int a[]) {
    a[2] = 55;
}

int main(int argc, char *argv[]) {
    //int a[]; // this does not work
    int b[10];
    //int c[] = new int[5]; // this does not work
    int *d = new int[5];
    for (int i = 0; i < 5; i++) d[i] = 23;
    for (int i = 0; i < 5; i++) cout << d[i] << " ";
    cout << "\n";
    func(d);
    func(d, 5);
    func2(d);
    func3(d);
    func(d, 5);
    return 0;
}