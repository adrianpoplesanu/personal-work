#include <iostream>

void show(int *a, int *drum, int poz) {
    if (drum[poz] != -1) {
        show(a, drum, drum[poz]);
    }
    std::cout << a[poz] << " ";
}

int main(int argc, char *argv[]) {
    int dp[100], drum[100];
    int a[] = {1, 9, 2, 9, 3, 9, 4, 9, 5, 9, 6, 9, 7}, n = 13, max, poz;
    memset(dp, 10, 0);
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            drum[i] = -1;
            dp[i] = 1;
            max = 1;
            poz = 0;
        } else {
            dp[i] = 1;
            drum[i] = -1;
            for (int j = 0; j < i; j++) if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                drum[i] = j;
            }
            if (max < dp[i]) {
                max = dp[i];
                poz = i;
            }
        }
    }
    std::cout << max << "\n";
    show(a, drum, poz);
    std::cout << "\n";
    return 0;
}
