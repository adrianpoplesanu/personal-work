// http://info.mcip.ro/?cap=Backtracking #817
#include <iostream>

int cmmdc(int a, int b) {
    while(a != b) {
        if (a > b) a -= b;
        else if (b > a) b -= a;
    }
    return a;
}

int calculate_cmmdc(int numbers[], int a[], int n) {
    if (n == 0) return numbers[a[0]];
    int res = cmmdc(numbers[a[0]], numbers[a[1]]);
    for (int i = 1; i <= n; i++) {
        res = cmmdc(res, numbers[a[i]]);
    }
    return res;
}

void print(int numbers[], int a[], int m) {
    for (int i = 0; i < m; i++) {
        std::cout << numbers[a[i]] << " ";
    }
    std::cout << "\n";
}

bool accept(int numbers[], int a[], int n, int m, int p, int k) {
    for (int i = 0; i < k; i++) if (a[i] >= a[k]) return false;
    if (calculate_cmmdc(numbers, a, k) < p) return false;
    return true;
}

void back(int numbers[], int a[], int n, int m, int p, int k) {
    if (k == m) {
        print(numbers, a, m);
    } else {
        a[k] = 0;
        while(a[k] < n) {
            if (accept(numbers, a, n, m, p, k)) {
                back(numbers, a, n, m, p, k + 1);
            }
            a[k]++;
        }
    }
}

int main(int argc, char *argv[]) {
    int n = 7, m = 3, p = 5;
    int numbers[] = { 3, 6, 9, 15, 20, 24, 30 };
    int a[n];
    memset(a, 0, sizeof(a));
    back(numbers, a, n, m, p, 0);
    return 0;
}
