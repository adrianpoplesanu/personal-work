#include <iostream>
#include <ctime>
using namespace std;

void Bk(int i, int n, int a[4]) {
    for (int j = 0; j < i; j++)
        for (int k = j + 1; k < i; k++)
            if (a[k] == a[j]) {
                return;
            }
    if (i == n) {
        //for (int j = 0; j < n; j++) cout << a[j] << " ";
        //cout << endl;
        return;
    }
    while(a[i] < n) {
        a[i]++;
        Bk(i + 1, n, a);
    }
    a[i] = 0;
}

int main(int argc, char *argv[]) {
    int n = 8, a[8];
    cout << "running..." << endl;
    clock_t start = clock();
    for (int i = 0; i < n; i++) a[i] = 0;
    Bk(0, n, a);
    clock_t end = clock();
    cout << "ran for " << double(end - start) / CLOCKS_PER_SEC << "secs" << endl;
    return 0;
}
