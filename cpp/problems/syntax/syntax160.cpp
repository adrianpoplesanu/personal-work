#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int a[10];
    memset(a, 0, sizeof(a));
    for (int i = 0; i < 10; i++) cout << a[i] << " ";
    for (int i = 0; i < 10; i++) a[i] = i * i;
    cout << "\n";
    for (auto element : a) {
        element += 1;
        cout << element << " ";
    }
    cout << "\n";
    for (auto element : a) {
        cout << typeid(element).name() << " " << element << " ";
    }
    cout << "\n";
    return 0;
}
