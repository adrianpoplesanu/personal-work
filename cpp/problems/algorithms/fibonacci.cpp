#include <iostream>
#include <time.h>
using namespace std;

void fib_dp(int n) {
    int values[n + 2];
    values[0] = 0;
    values[1] = 1;
    for(int i = 2; i <= n; i++) {
        values[i] = values[i-1] + values[i-2];
    }
    cout << values[n] << endl;
}

void fib_opt(int n) {
    int a = 0;
    int b = 1;
    int c;
    while(n--) {
        c = a + b;
        a = b;
        b = c;
    }
    cout << a << endl; 
}

int main(int argc, char* atgv[]) {
    clock_t tstart = clock();
    fib_dp(10);
    cout << "execution time: " << (double)(clock() - tstart) / CLOCKS_PER_SEC << endl;
    tstart = clock();
    fib_opt(10);
    cout << "execution time: " << (double)(clock() - tstart) / CLOCKS_PER_SEC << endl;
    return 0;
}
