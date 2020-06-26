#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    char a[] = {84, 104, 105, 115, 32, 105, 115, 32, 117, 115, 101, 108, 101, 115, 115, 33};
    for (int i = 0; i < 16; i++) {
        cout << (char)a[i];
    }
    cout << "\n";
    return 0;
}
