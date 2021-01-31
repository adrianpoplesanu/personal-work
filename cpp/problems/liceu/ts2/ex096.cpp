// ts2 p47 e18
#include <iostream>
using namespace std;

int binary_search(int a[100], int l, int r, int value) {
    //cout << l << " " << r << "\n";
    if (l == r) if (a[l] == value) return 1;
                else return 0;
    else {
        int mid = (l + r) / 2;
        if (a[mid] == value) return 1;
        if (a[mid] < value) return binary_search(a, mid + 1, r, value);
        else return binary_search(a, l, mid - 1, value);
    }
}

int main(int argc, char *argv[]) {
    int a[10] = {1, 2, 4, 6, 7, 9}, n = 6;
    cout << binary_search(a, 0, n - 1, 7) << "\n";
    cout << binary_search(a, 0, n - 1, 5) << "\n";
    return 0;
}
