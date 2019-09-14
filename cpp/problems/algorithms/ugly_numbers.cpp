#include<iostream>
#include<iomanip>
using namespace std;

int min(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    if (b <= a && b <= c) return b;
    return c;
}

void ugly(int n) {
    int u[n];
    int next_2 = 2;
    int next_3 = 3;
    int next_5 = 5;
    int i2 = 0, i3 = 0, i5 = 0;
    cout<<setw(3)<<1<<":"<<setw(5)<<1<<endl;
    u[0] = 1;
    for(int i = 1; i < n; i++) {
        int next = min(next_2, next_3, next_5);
        u[i] = next;
        if (next == next_2) {
            i2++;
            next_2 = 2 * u[i2];
        }
        if (next == next_3) {
            i3++;
            next_3 = 3 * u[i3];
        }
        if (next == next_5) {
            i5++;
            next_5 = 5 * u[i5];
        }
        cout<<setw(3)<<i+1<<":"<<setw(5)<<next<<endl;
    }
}

int main(int argc, char* argv[]) {
    int n = 150;
    ugly(n);
    return 0;
}
