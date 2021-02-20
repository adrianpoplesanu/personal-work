// permutari simple
#include <iostream>
using namespace std;

void display(int a[10], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
}

bool accept(int a[10], int k, int n) {
    for (int i = 0; i < k; i++) {
        if (a[i] == a[k]) return false;
    }
    return true;
}

void back(int a[10], int k, int n) {
    if (k == n) display(a, n);
    a[k] = 0;
    while(a[k] < n) {
        if (accept(a, k, n)) {
            back(a, k + 1, n);
        }
        a[k]++;
    }
}

int main(int argc, char *argv[]) {
    int a[10], n = 3;
    back(a, 0, n);
    return 0;
}
