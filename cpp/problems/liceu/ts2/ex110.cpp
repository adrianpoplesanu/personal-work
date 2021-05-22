// ts2 p70 e1
#include <iostream>

int st[10000][2];

int main(int argc, char *argv[]) {
    int m, n, k;
    std::cout << "m = "; std::cin >> m;
    std::cout << "n = "; std::cin >> n;
    k = 1;
    st[k][0] = m;
    st[k][1] = n;
    while(k > 0) {
        if (st[k][0] && st[k][1]) {
            k++;
            st[k][0] = st[k - 1][0];
            st[k][1] = st[k - 1][1] - 1;
        } else {
            if (!st[k][1]) {
                st[k][0] = st[k][0] - 1;
                st[k][1] = 1;
            } else {
                k--;
                if (k > 0) {
                    st[k][0] = st[k][0] - 1;
                    st[k][1] = st[k + 1][1] + 1;
                }
            }
        }
    }
    std::cout << "ac(" << m << ", " << n << ") = " << st[1][1] + 1 << "\n";
    return 0;
}
