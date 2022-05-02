#include <iostream>

int a[100];

bool check(int k, int n) {
    for (int i = 0; i < k; i++) if (a[i] == a[k]) return false;
    return true;
}

void back(int k, int n) {
    if (k == n) {
        for (int i = 0; i < n; i++) std::cout << a[i] << " ";
        std::cout << "\n";
    }
    a[k] = 0;
    while(a[k] < n) {
        if (check(k, n)) {
            back(k + 1, n);
        }
        a[k]++;
    }
}

int main(int argc, char *argv[]) {
    back(0, 3);
    return 0;
}
