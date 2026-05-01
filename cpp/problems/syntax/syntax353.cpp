#include <iostream>

int n = 3;
int a[10];

bool check(int k) {
    for (int i = 0; i < k; i++) {
        if (a[i] == a[k]) return false;
    }
    return true;
}

void print() {
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " " ;
    }
    std::cout << '\n';
}

void back(int k) {
    if (k == n) {
        print();
    } else {
        a[k] = 0;
        while (a[k] < 3) {
            a[k]++;
            if (check(k)) {
                back(k + 1);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    back(0);
    return 0;
}
