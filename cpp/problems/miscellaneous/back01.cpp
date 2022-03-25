// permutations
#include <iostream>

bool check(int i, int a[]) {
    for (int j = 0; j < i; j++) if (a[j] == a[i]) return false;
    return true;
}

void back(int i, int n, int a[]) {
    if (i == n) {
        for (int j = 0; j < n; j++) std::cout << a[j] << " ";
        std::cout << "\n";
    } else {
        a[i] = 1;
        while(a[i] <= n) {
            if (check(i, a)) {
                back(i + 1, n, a);
            }
            a[i]++;
        }
        a[i] = 0;
    }
}

int main(int argc, char *argv[]) {
    int n = 3;
    int a[n];
    back(0, n, a);
    return 0;
}