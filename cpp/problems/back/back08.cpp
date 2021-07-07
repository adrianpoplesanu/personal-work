// http://info.mcip.ro/?cap=Backtracking #811
#include <iostream>

bool sol(int pct[], int a[], int n, int low, int high, int min, int max) {
    int total = 0, sum = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
            total++;
            sum += pct[i];
        }
    }
    return (low <= total) && (total <= high) && (min <= sum) && (sum <= max);
}

void show(int pct[], int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) std::cout << pct[i] << " ";
    }
    std::cout << "\n";
}

void back(int pct[], int a[], int n, int low, int high, int min, int max, int k) {
    if (k == n) {
        if (sol(pct, a, n, low, high, min, max)) show(pct, a, n);
    } else {
        a[k] = 0;
        while(a[k] < 2) {
            back(pct, a, n, low, high, min, max, k + 1);
            a[k]++;
        }
    }
}


int main(int argc, char *argv[]) {
    int n = 7, a = 4, b = 5, p = 20, q = 25;
    int pct[] = { 6, 5, 7, 8, 2, 3, 10 };
    int v[n];
    memset(v, 0, sizeof(v));
    back(pct, v, n, a, b, p, q, 0);
    return 0;
}
