// caractere eligibile de la 41 pana la 176

#include <iostream>

void print(int a[16], int n) {
    for (int i = 0; i < n; i++) {
        char c = a[i];
        std::cout << c;
    }
    std::cout << "\n";
}

bool accept(int a[16], int n, int m, int k) {
    return true;
}

void back(int a[16], int n, int m, int k) {
    if (k == n) {
        print(a, n);
    } else {
        a[k] = 41;
        while (a[k] < m) {
            if(accept(a, n, m, k)) back(a, n, m, k + 1);
            a[k]++;
        }
    }
}

int main(int argc, char *argv[]) {
    int a[16], m = 176, n = 2;
    back(a, n, m, 0);
    return 0;
}
