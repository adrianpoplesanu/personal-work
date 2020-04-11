#include <iostream>
using namespace std;

int a[10], n;

void init(int k) {
    a[k] = 0;
}

int e_sol(int k) {
    return k == n;
}

int e_valid(int k) {
    for(int i = 0; i < k; i++) {
        if (a[i] == a[k]) return 0;
    }
    return 1;
}

void tipar() {
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
}

void back(int k) {
    if (k < 0) return;
    if (e_sol(k)) {
        tipar();
    } else {
        while (a[k] < n) {
            a[k]++;
            if (e_valid(k)) { 
                init(k + 1);
                back(k + 1);
            }
        } 
        init(k);
    }
}

int main(int argc, char *argv[]) {
    cout << "n = "; cin >> n;
    back(0);
    return 0;
}
