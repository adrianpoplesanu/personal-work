// http://info.mcip.ro/?cap=Backtracking #812
#include <iostream>

void print(int a[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << a[i];
    }
    std::cout << "\n";
}

bool accept(int a[], int n, int k) {
    if (k == 0) return a[0] == 0;
    else {
        if (k == n - 1) return (a[k] == 0) && (a[k - 1] == a[k] - 1 || a[k - 1] == a[k] + 1);
        else {
            return a[k - 1] == a[k] - 1 || a[k - 1] == a[k] + 1;
        }
    }
}

void back(int a[], int n, int k) {
    if (k == n) {
        print(a, n);
    } else {
        a[k] = 0;
        while(a[k] < n) {
            if (accept(a, n, k)) {
                back(a, n, k + 1);
            }
            a[k]++;
        }
    }
}

int main(int argc, char *argv[]) {
    int n = 19;
    int a[n];
    memset(a, 0, sizeof(a));
    back(a, n, 0);
    return 0;
}
