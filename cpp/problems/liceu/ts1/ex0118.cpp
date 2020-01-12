// TS1 e2 p143 pdf
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n;
    float a[10];
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "] = "; cin >> a[i];
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
    return 0;
}
