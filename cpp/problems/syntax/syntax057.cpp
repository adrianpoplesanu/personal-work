#include <iostream>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]) {
    int k, v[1500000];
    cout << "k = "; cin >> k;
    clock_t begin = clock();
    for (int i = 0; i < 1500000; i++) v[i] = 0;
    v[0] = 1; v[1] = 1;
    for (int i = 2; i < 1500000; i++) {
        for (int j = i * 2; j < 1500000; j += i) {
            if (v[j] == 0) v[j] = 1;
        }
    }
    int m = 0;
    int i = 0;
    while(m < k) {
        if (v[i] == 0) {
            m++;
        }
        i++;
    }
    cout << --i << endl;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "ran for: " << elapsed_secs << "sec" << endl;
    return 0;
}
