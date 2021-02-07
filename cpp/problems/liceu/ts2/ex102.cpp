// ts2 p48 e24
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int n;
    cout << "n = "; cin >> n;
    for (int i = 0; i < n; i++) {
        int current = i + 1;
        current = current % 10;
        for (int j = 0; j <= i; j++) {
            cout << current++;
            if (current > 9) current = 0;
        }
        current--;
        if (current < 0) current = 9;
        for (int j = 0; j < i; j++) {
            current--;
            if (current < 0) current = 9;
            cout << current;
        }
        cout << "\n";
    }
    return 0;
}
