#include <iostream>

bool check(int *a, int n, int k) {
    for (int i = 0; i < k; i++) if (a[i] == a[k]) return false;
    return true;
}

void back(int *a, int n, int k) {
    if (k == 3) {
        std::cout << "[";
        for (int i = 0; i < n; i++) {
            if (i < n - 1) std::cout << a[i] << ", ";
            else std::cout << a[i];
        }
        std::cout << "]\n";
    } else {
        for (int j = 0; j < 3; j++) {
            a[k] = j;
            if (check(a, n, k)) {
                back(a, n, k + 1);
            }
            a[k] = 0;
        }
    }
}

int main(int argc, char* argv[]) {
    int a[10];
    memset(a, 10, 0);
    back(a, 3, 0);
    return 0;
}
